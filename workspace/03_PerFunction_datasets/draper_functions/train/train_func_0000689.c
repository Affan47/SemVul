chomp(char *string)
{
  int length = strlen(string) - 1;

  if(length >= 0 && string[length] == '\n')
    string[length] = '\0';

  return length;
}
