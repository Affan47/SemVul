asProperties() const
{
  PropertyMap map;
  String tagName = txxxToKey(description());
  StringList v = fieldList();
  for(StringList::ConstIterator it = v.begin(); it != v.end(); ++it)
    if(it != v.begin())
      map.insert(tagName, *it);
  return map;
}
