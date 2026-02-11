AllocateParserType(cmDependsJavaParserHelper::ParserType* pt,
                     const char* str, int len)
{
  pt->str = 0;
  if ( len == 0 )
    {
    len = (int)strlen(str);
    }
  if ( len == 0 )
    {
    return;
    }
  this->UnionsAvailable ++;
  pt->str = new char[ len + 1 ];
  strncpy(pt->str, str, len);
  pt->str[len] = 0;
  this->Allocates.push_back(pt->str);
}
