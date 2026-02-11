get_line(char *buffer, FILE *fp)
{
  int current;
  int escape_1 = 0;
  int i;


  for(i = 0; i < 256; i++)
  {
    current = fgetc(fp);
    if(current == -1)
    {
      return -1;
    }
    if(current == '\"')
    {
      if(escape_1 == 0)
      {
        escape_1 = 1;
      }
      else
      {
        escape_1 = 0;
      }
    }

    if(!escape_1)
    {
      if(current == '\r')
      {
        fgetc(fp);
        buffer[i] = 0;
        return 0;
      }

      if(current == '\n')
      {
        buffer[i] = 0;
        return 0;
      }
    }
    buffer[i] = current;
  }
  buffer[255] = 0;

  return -2;
}
