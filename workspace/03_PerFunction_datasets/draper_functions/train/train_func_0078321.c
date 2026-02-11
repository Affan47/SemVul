read()
{


  ByteVector data = d->file->packet(0);

  int pos = 28;


  d->speexVersion = data.mid(pos, 4).toUInt(false);
  pos += 4;


  pos += 4;


  d->sampleRate = data.mid(pos, 4).toUInt(false);
  pos += 4;


  d->mode = data.mid(pos, 4).toUInt(false);
  pos += 4;


  pos += 4;


  d->channels = data.mid(pos, 4).toUInt(false);
  pos += 4;


  d->bitrate = data.mid(pos, 4).toUInt(false);
  pos += 4;


  pos += 4;


  d->vbr = data.mid(pos, 4).toUInt(false) == 1;
  pos += 4;


  const Ogg::PageHeader *first = d->file->firstPageHeader();
  const Ogg::PageHeader *last = d->file->lastPageHeader();

  if(first && last) {
    long long start = first->absoluteGranularPosition();
    long long end = last->absoluteGranularPosition();

    if(start >= 0 && end >= 0 && d->sampleRate > 0)
      d->length = (int) ((end - start) / (long long) d->sampleRate);
    else
      debug("Speex::Properties::read() -- Either the PCM values for the start or "
            "end of this file was incorrect or the sample rate is zero.");
  }
  else
    debug("Speex::Properties::read() -- Could not find valid first and last Ogg pages.");
}
