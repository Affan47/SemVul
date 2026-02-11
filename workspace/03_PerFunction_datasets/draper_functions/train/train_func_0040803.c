soundslike_chars() const
    {
      bool chars_set[256] = {0};
      String     chars_list;
      for (const char * * i = phonet_parms->rules + 1;
	   *(i-1) != PhonetParms::rules_end;
	   i += 2)
      {
        for (const char * j = *i; *j; ++j)
        {
          chars_set[static_cast<unsigned char>(*j)] = true;
        }
      }
      for (int i = 0; i != 256; ++i)
      {
        if (chars_set[i])
          chars_list += static_cast<char>(i);
      }
      return chars_list;
    }
