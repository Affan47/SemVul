refPart(const StringC &id)
{
  for (IListIter<PartHeader> iter(headers_); !iter.done(); iter.next())
    if (iter.cur()->id() == id)
      return iter.cur();
  PartHeader *header = new PartHeader(this, id);
  headers_.insert(header);
  return header;
}
