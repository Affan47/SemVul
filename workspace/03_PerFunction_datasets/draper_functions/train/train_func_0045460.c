itoc(int i)
{
  if (i <= 0)
    return '?';
  else if (i <= 26)
    return 'a' + i - 1;
  else if (i <= 52)
    return 'A' + i - 27;
  else
    return '?';
}
