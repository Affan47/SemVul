GetValueAsList( Option option )
{
  METAIO_STL::list<METAIO_STL::string> results;
  results.clear();
  METAIO_STL::vector<Field>::const_iterator itField = option.fields.begin();
  ++itField;
  while(itField != option.fields.end())
    {
    results.push_back((*itField).value);
    ++itField;
    }
  return results;
}
