parseFields(const ByteVector &data)
{
  if(data.size() < 5) {
    debug("A picture frame must contain at least 5 bytes.");
    return;
  }

  d->textEncoding = String::Type(data[0]);

  int pos = 1;

  d->mimeType = readStringField(data, String::Latin1, &pos);

  if (uint(pos) + 1 >= data.size()) {
    debug("Truncated picture frame.");
    return;
  }

  d->type = (TagLib::ID3v2::AttachedPictureFrame::Type)data[pos++];
  d->description = readStringField(data, d->textEncoding, &pos);

  d->data = data.mid(pos);
}
