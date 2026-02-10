GetStringSize(char *string, int level)
{

  if (level > this->MaxFontLevel)
    {
    level = this->MaxFontLevel;
    }
  int size = 0, i;
  for(i = 0; string[i] != '\0'; i++)
    {
    if (string[i] < 32)
      {
      continue;
      }

    if (string[i] > 126)
      {
      continue;
      }

    size += this->FontWidths[level][string[i]-32];
    }
  return size;
}
