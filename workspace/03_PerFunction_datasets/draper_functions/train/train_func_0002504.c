parseFields(const ByteVector &data)
{
  if(data.size() < 5) {
    debug("A picture frame must contain at least 5 bytes.");
    return;
  }

  d->textEncoding = String::Type(data[0]);

  int pos = 1;

  String fixedString = String(data.mid(pos, 3), String::Latin1);
  pos += 3;

  if (fixedString.upper() == "JPG") {
    d->mimeType = "image/jpeg";
  } else if (fixedString.upper() == "PNG") {
    d->mimeType = "image/png";
  } else {
    debug("probably unsupported image type");
    d->mimeType = "image/" + fixedString;
  }

  d->type = (TagLib::ID3v2::AttachedPictureFrame::Type)data[pos++];
  d->description = readStringField(data, d->textEncoding, &pos);

  d->data = data.mid(pos);
}
