GetArgument(const char *argName)
{
  string argValue
    = vtkTestingGetArgOrEnvOrDefault(argName,this->Args,"","");

  char *cArgValue=new char [argValue.size()+1];
  strcpy(cArgValue,argValue.c_str());

  return cArgValue;
}
