getFieldValueBySifName(const char* name, int& value, bool only_active)
{
  ParameterField* pf = getFieldBySifName(name, only_active);

  if (pf == NULL)
    return false;

  char** data = pf->getDataStrings();

  if ( !LibFront::isNumber(data[0]) )
    return false;

  value = atol(data[0]);


  return true;
}
