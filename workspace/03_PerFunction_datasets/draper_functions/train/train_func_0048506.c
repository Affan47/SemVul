cut_bin (char * in)
{
  size_t p;

  if (NULL == in)
    return NULL;
  p = strlen (in);
  if (p < 4)
    return in;
  if ( ('/' == in[p-1]) ||
       ('\\' == in[p-1]) )
    in[--p] = '\0';
  if (0 == strcmp (&in[p-4],
		   "/bin"))
    {
      in[p-4] = '\0';
      p -= 4;
    }
  else if (0 == strcmp (&in[p-4],
			"\\bin"))
    {
      in[p-4] = '\0';
      p -= 4;
    }
  return in;
}
