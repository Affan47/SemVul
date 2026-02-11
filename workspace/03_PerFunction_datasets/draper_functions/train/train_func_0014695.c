buffer_create(ESL_BUFFER **ret_bf)
{
  ESL_BUFFER *bf  = NULL;
  int         status;

  ESL_ALLOC(bf, sizeof(ESL_BUFFER));
  bf->mem        = NULL;
  bf->n          = 0;
  bf->balloc     = 0;
  bf->pos        = 0;
  bf->baseoffset = 0;
  bf->anchor     = -1;
  bf->fp         = NULL;
  bf->filename   = NULL;
  bf->cmdline    = NULL;
  bf->pagesize   = eslBUFFER_PAGESIZE;
  bf->errmsg[0]  = '\0';
  bf->mode_is    = eslBUFFER_UNSET;

  *ret_bf = bf;
  return eslOK;

 ERROR:
  if (bf) free(bf);
  *ret_bf = NULL;
  return status;
}
