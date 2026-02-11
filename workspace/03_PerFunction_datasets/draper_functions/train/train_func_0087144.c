PrettySize(float size, char *str)
{
  if (size > 1073741824)
    sprintf (str, "%.1fGb", size / 1073741824.);
  else
    if (size > 1048576)
      sprintf (str, "%.1fMb", size / 1048576.);
    else
      sprintf (str, "%.1fkb", size / 1024.);
  return (str);
}
