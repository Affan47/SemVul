is_variable_keyword(char* str)
{
  LibFront::toLower(str);
  if ( 0 == strcmp(str, "variable") )
    return true;
  else
    return false;
}
