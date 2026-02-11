SetOption(METAIO_STL::string name,
                            METAIO_STL::string tag,
                            bool required,
                            METAIO_STL::string description,
                            TypeEnumType type,
                            METAIO_STL::string defVal)
{

  if(tag == "")
    {
    METAIO_STREAM::cout << "Tag cannot be empty :\
                           use AddField()\
                           instead." << METAIO_STREAM::endl;
    return false;
    }

  Option option;
  option.tag = tag;
  option.name = name;
  option.required = required;
  option.description = description;
  option.userDefined = false;
  option.complete = false;


  Field field;
  if(type == LIST)
    {
    field.name = "NumberOfValues";
    }
  else
    {
    field.name = name;
    }
  field.externaldata = DATA_NONE;
  field.type = type;
  field.value = defVal;
  field.userDefined = false;
  field.required = true;
  field.rangeMin = "";
  field.rangeMax = "";
  option.fields.push_back(field);

  m_OptionVector.push_back(option);
  return true;
}
