soap_getposition(const char *attr, int *pos)
{ register int i, n;
  if (!*attr)
    return -1;
  n = 0;
  i = 1;
  do
  { pos[n++] = (int)atol(attr + i);
    while (attr[i] && attr[i] != ',' && attr[i] != ']')
      i++;
    if (attr[i] == ',')
      i++;
  } while (n < SOAP_MAXDIMS && attr[i] && attr[i] != ']');
  return n;
}
