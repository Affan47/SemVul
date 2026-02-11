EvaluatingIncludeDirectories() const
{
  const char *prop = this->Property.c_str();
  return (strcmp(prop, "INCLUDE_DIRECTORIES") == 0
       || strcmp(prop, "INTERFACE_INCLUDE_DIRECTORIES") == 0 );
}
