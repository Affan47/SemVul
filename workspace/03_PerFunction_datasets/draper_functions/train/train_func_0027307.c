reopen_fstreams(const char *filename,
                                   FILE *outstream, FILE *errstream)
{
  if (outstream && !my_freopen(filename, "a", outstream))
    return TRUE;

  if (errstream && !my_freopen(filename, "a", errstream))
    return TRUE;


  if (errstream)
    setbuf(errstream, NULL);

  return FALSE;
}
