utf8_to_latin1(char *utf8_str)
{
  int i, j, len;

  unsigned char *str;


  str = (unsigned char *)utf8_str;

  len = strlen(utf8_str);

  if(!len)
  {
    return;
  }

  j = 0;

  for(i=0; i<len; i++)
  {
    if((str[i] < 32) || ((str[i] > 127) && (str[i] < 192)))
    {
      str[j++] = '.';

      continue;
    }

    if(str[i] > 223)
    {
      str[j++] = 0;

      return;
    }

    if((str[i] & 224) == 192)
    {
      if((i + 1) == len)
      {
        str[j++] = 0;

        return;
      }

      if((str[i] & 252) != 192)
      {
        str[j++] = '.';

        i++;

        continue;
      }

      if((str[i + 1] & 192) != 128)
      {
        str[j++] = 0;

        return;
      }

      str[j] = str[i] << 6;
      str[j] += (str[i + 1] & 63);

      i++;
      j++;

      continue;
    }

    str[j++] = str[i];
  }

  if(j<len)
  {
    str[j] = 0;
  }
}
