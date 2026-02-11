is_empty_string (const char* str)
{
  int return_value = 0;

  if (str != 0)
    {
      int i = 0;

      while (str[i] != '\0')
        {
          if (str[i] != ' ')
            {
              break;
            }

          ++i;
        }

      if (str[i] == '\0')
        {
          return_value = 1;
        }
    }

  return return_value;
}
