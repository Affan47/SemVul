readBlock(ulong length)
{
  if(length == 0)
    return ByteVector::null;

  ByteVector v = d->data.mid(d->position, length);
  d->position += v.size();
  return v;
}
