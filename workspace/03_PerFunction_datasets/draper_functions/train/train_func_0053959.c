GetValueAsFloat(Option option,
                METAIO_STL::string fieldName)
{
  METAIO_STL::string fieldname = fieldName;
  if(fieldName == "")
    {
    fieldname = option.name;
    }

  METAIO_STL::vector<Field>::const_iterator itField = option.fields.begin();
  while(itField != option.fields.end())
    {
    if((*itField).name == fieldname)
      {
      return (float)atof((*itField).value.c_str());
      }
    ++itField;
    }
  return 0;
}
