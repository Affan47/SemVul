parseFields(const ByteVector &data)
{
  int pos = 0, size = int(data.size());

  d->email = readStringField(data, String::Latin1, &pos);

  d->rating = 0;
  d->counter = 0;
  if(pos < size) {
    d->rating = (unsigned char)(data[pos++]);
    if(pos < size) {
      d->counter = data.mid(pos, 4).toUInt();
    }
  }
}
