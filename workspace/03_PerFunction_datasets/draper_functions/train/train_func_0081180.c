AddOptionField(METAIO_STL::string optionName,
               METAIO_STL::string name,
               TypeEnumType type,
               bool required,
               METAIO_STL::string defVal,
               METAIO_STL::string description,
               DataEnumType externalData)
{
  OptionVector::iterator it = m_OptionVector.begin();
  while(it != m_OptionVector.end())
    {
    if((*it).name == optionName)
      {

      Field field;
      field.name = name;
      field.type = type;
      field.required = required;
      field.value = defVal;
      field.description = description;
      field.userDefined = false;
      field.externaldata = externalData;
      field.rangeMin = "";
      field.rangeMax = "";


      if((*it).fields[0].type == FLAG)
        {
        (*it).fields[0] = field;
        }
      else
        {
        (*it).fields.push_back(field);
        }
      return true;
      }
    it++;
    }
  return false;
}
