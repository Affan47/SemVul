GetAttribute(const char* name, const char** atts)
    {
      int i = 0;
      for(; atts[i] != 0; ++i)
        {
        if(strcmp(name, atts[i]) == 0)
          {
          return atts[i+1];
          }
        }
      return 0;
    }
