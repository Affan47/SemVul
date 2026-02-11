scan()
{


  if(d->scanned)
    return;

  if(!isValid())
    return;

  long nextBlockOffset;

  if(d->hasID3v2)
    nextBlockOffset = find("fLaC", d->ID3v2Location + d->ID3v2OriginalSize);
  else
    nextBlockOffset = find("fLaC");

  if(nextBlockOffset < 0) {
    debug("FLAC::File::scan() -- FLAC stream not found");
    setValid(false);
    return;
  }

  nextBlockOffset += 4;
  d->flacStart = nextBlockOffset;

  seek(nextBlockOffset);

  ByteVector header = readBlock(4);


  char blockType = header[0] & 0x7f;
  bool isLastBlock = (header[0] & 0x80) != 0;
  uint length = header.mid(1, 3).toUInt();


  if(blockType != MetadataBlock::StreamInfo) {
    debug("FLAC::File::scan() -- invalid FLAC stream");
    setValid(false);
    return;
  }

  d->streamInfoData = readBlock(length);
  d->blocks.append(new UnknownMetadataBlock(blockType, d->streamInfoData));
  nextBlockOffset += length + 4;


  while(!isLastBlock) {

    header = readBlock(4);
    blockType = header[0] & 0x7f;
    isLastBlock = (header[0] & 0x80) != 0;
    length = header.mid(1, 3).toUInt();

    ByteVector data = readBlock(length);
    if(data.size() != length || length == 0) {
      debug("FLAC::File::scan() -- FLAC stream corrupted");
      setValid(false);
      return;
    }

    MetadataBlock *block = 0;


    if(blockType == MetadataBlock::VorbisComment) {
      if(!d->hasXiphComment) {
        d->xiphCommentData = data;
        d->hasXiphComment = true;
      }
      else {
        debug("FLAC::File::scan() -- multiple Vorbis Comment blocks found, using the first one");
      }
    }
    else if(blockType == MetadataBlock::Picture) {
      FLAC::Picture *picture = new FLAC::Picture();
      if(picture->parse(data)) {
        block = picture;
      }
      else {
        debug("FLAC::File::scan() -- invalid picture found, discarting");
        delete picture;
      }
    }

    if(!block) {
      block = new UnknownMetadataBlock(blockType, data);
    }
    if(block->code() != MetadataBlock::Padding) {
      d->blocks.append(block);
    }
    else {
      delete block;
    }

    nextBlockOffset += length + 4;

    if(nextBlockOffset >= File::length()) {
      debug("FLAC::File::scan() -- FLAC stream corrupted");
      setValid(false);
      return;
    }
    seek(nextBlockOffset);
  }


  d->streamStart = nextBlockOffset;
  d->streamLength = File::length() - d->streamStart;

  if(d->hasID3v1)
    d->streamLength -= 128;

  d->scanned = true;
}
