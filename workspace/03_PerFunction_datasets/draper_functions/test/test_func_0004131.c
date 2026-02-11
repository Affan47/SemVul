dataSize() const
{
  switch (d->type) {
  case WordType:
    return 2;
  case BoolType:
    return 4;
  case DWordType:
    return 4;
  case QWordType:
    return 5;
  case UnicodeType:
    return d->stringValue.size() * 2 + 2;
  case BytesType:
    if(d->pictureValue.isValid())
      return d->pictureValue.dataSize();
  case GuidType:
    return d->byteVectorValue.size();
  }
  return 0;
}
