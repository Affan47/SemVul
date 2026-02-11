renderInt(const ByteVector &name, MP4::Item &item)
{
  ByteVectorList data;
  data.append(ByteVector::fromShort(item.toInt()));
  return renderData(name, TypeInteger, data);
}
