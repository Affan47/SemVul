skipWhite ()
{
  int32 i = filepointer;
  while (data [i] == ' ' || data [i] == '\t') i ++;
  filepointer = i;
}
