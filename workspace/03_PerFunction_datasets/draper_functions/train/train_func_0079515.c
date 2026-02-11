ValidateGlobalAttribute(
  const char *attname, vtkDataArray *vtkNotUsed(array))
{

  static const char *globalAttributes[] = {
    MIident,
    MIhistory,
    MItitle,
    0
  };
  const int autoGlobalAttributes = 2;

  int itry = 0;
  for (itry = 0; globalAttributes[itry] != 0; itry++)
    {
    if (strcmp(attname, globalAttributes[itry]) == 0)
      {
      break;
      }
    }
  if (itry < autoGlobalAttributes)
    {

    return 0;
    }
  else if (globalAttributes[itry] == 0)
    {
    return 2;
    }

  return 1;
}
