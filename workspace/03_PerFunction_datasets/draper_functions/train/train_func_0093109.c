AskUser(const char* key,
  cmCacheManager::CacheIterator& iter)
{
  printf("Variable Name: %s\n", key);
  const char* helpstring = iter.GetProperty("HELPSTRING");
  printf("Description: %s\n", (helpstring?helpstring:"(none)"));
  printf("Current Value: %s\n", iter.GetValue());
  printf("New Value (Enter to keep current value): ");
  char buffer[4096];
  if(!fgets(buffer, sizeof(buffer)-1, stdin))
    {
    buffer[0] = 0;
    }

  if(strlen(buffer) > 0)
    {
    std::string sbuffer = buffer;
    std::string::size_type pos = sbuffer.find_last_not_of(" \n\r\t");
    std::string value = "";
    if ( pos != std::string::npos )
      {
      value = sbuffer.substr(0, pos+1);
      }

    if ( value.size() > 0 )
      {
      if(iter.GetType() == cmCacheManager::PATH ||
         iter.GetType() == cmCacheManager::FILEPATH)
        {
        cmSystemTools::ConvertToUnixSlashes(value);
        }
      if(iter.GetType() == cmCacheManager::BOOL)
        {
        if(!cmSystemTools::IsOn(value.c_str()))
          {
          value = "OFF";
          }
        }
      iter.SetValue(value.c_str());
      }
    }
  printf("\n");
}
