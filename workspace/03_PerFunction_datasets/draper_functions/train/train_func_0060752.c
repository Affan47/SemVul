basename_into(char *tmp, char *target)
{
  unsigned int len, ii;

  len = strlen(tmp);
  for (ii = len; ii > 0; )
    if (tmp[--ii] == '/')
      break;
  if (ii < len - 1)
    return tmp + ii + (tmp[ii] == '/');
  else if (tmp[ii] != '/')
    return tmp;
  else if (ii == 0)
    return tmp;
  else
  {
    while (ii > 0)
      if (tmp[--ii] == '/')
         break;
    if (tmp[ii] == '/')
        ii++;
    for (len = 0; tmp[ii] != '/'; )
      target[len++] = tmp[ii++];
    target[len] = '\0';
    return target;
  }
}
