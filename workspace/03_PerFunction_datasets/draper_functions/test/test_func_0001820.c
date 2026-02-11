WritePropertyEntries(std::ostream& os,
                                          CacheIterator const& i)
{
  for(const char** p = this->PersistentProperties; *p; ++p)
    {
    if(const char* value = i.GetProperty(*p))
      {
      std::string helpstring = *p;
      helpstring += " property for variable: ";
      helpstring += i.GetName();
      cmCacheManager::OutputHelpString(os, helpstring);

      std::string key = i.GetName();
      key += "-";
      key += *p;
      this->OutputKey(os, key);
      os << ":INTERNAL=";
      this->OutputValue(os, value);
      os << "\n";
      }
    }
}
