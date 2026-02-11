parse(const ByteVector &data)
{


  if(data.size() < 11) {
    debug("APE::Item::parse() -- no data in item");
    return;
  }

  uint valueLength  = data.mid(0, 4).toUInt(false);
  uint flags        = data.mid(4, 4).toUInt(false);

  d->key = String(data.mid(8), String::UTF8);

  d->value = data.mid(8 + d->key.size() + 1, valueLength);

  setReadOnly(flags & 1);
  setType(ItemTypes((flags >> 1) & 3));

  if(int(d->type) < 2)
    d->text = StringList(ByteVectorList::split(d->value, '\0'), String::UTF8);
}
