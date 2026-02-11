export_section (const ACE_Configuration_Section_Key& section,
                                const ACE_TString& path,
                                FILE* out)
{

  if (path.length ())
    {

      ACE_TString header = ACE_TEXT ("[");
      header += path;
      header += ACE_TEXT ("]\n");
      if (ACE_OS::fputs (header.fast_rep (), out) < 0)
        return -1;

      int index = 0;
      ACE_TString name;
      ACE_Configuration::VALUETYPE type;
      ACE_TString line;
      ACE_TCHAR int_value[32];
      ACE_TCHAR bin_value[3];
      void* binary_data;
      size_t binary_length;
      ACE_TString string_value;
      while (!config_.enumerate_values (section, index, name, type))
        {
          line = name + ACE_TEXT ("=");
          switch (type)
            {
            case ACE_Configuration::INTEGER:
              {
                u_int value;
                if (config_.get_integer_value (section, name.fast_rep (), value))
                  return -2;
                ACE_OS::sprintf (int_value, ACE_TEXT ("%08x"), value);
                line += int_value;
                break;
              }
            case ACE_Configuration::STRING:
              {
                if (config_.get_string_value (section,
                                              name.fast_rep (),
                                              string_value))
                  return -2;
                line += string_value;
                break;
              }
#ifdef _WIN32
            case ACE_Configuration::INVALID:
              break;


#endif
            case ACE_Configuration::BINARY:
              {

                if (config_.get_binary_value (section,
                                              name.fast_rep (),
                                              binary_data,
                                              binary_length))
                  return -2;
                line += ACE_TEXT ("\"");
                unsigned char* ptr = (unsigned char*)binary_data;
                while (binary_length)
                  {
                    if (ptr != binary_data)
                      {
                        line += ACE_TEXT (",");
                      }
                    ACE_OS::sprintf (bin_value, ACE_TEXT ("%02x"), *ptr);
                    line += bin_value;
                    --binary_length;
                    ++ptr;
                  }
                line += ACE_TEXT ("\"");
                delete [] (char *) binary_data;
                break;
              }
            default:
              return -3;

            }

          line += ACE_TEXT ("\n");
          if (ACE_OS::fputs (line.fast_rep (), out) < 0)
            return -4;
          ++index;
        }
    }

  int index = 0;
  ACE_TString name;
  ACE_Configuration_Section_Key sub_key;
  ACE_TString sub_section;
  while (!config_.enumerate_sections (section, index, name))
    {
      ACE_TString sub_section (path);
      if (path.length ())
        sub_section += ACE_TEXT ("\\");
      sub_section += name;
      if (config_.open_section (section, name.fast_rep (), 0, sub_key))
        return -5;
      if (export_section (sub_key, sub_section.fast_rep (), out))
        return -6;
      ++index;
    }
  return 0;

}
