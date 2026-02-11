UUInitialize (void)
{
  allomap *aiter;

  progress.action     = 0;
  progress.curfile[0] = '\0';

  ftodel = NULL;

  uusavepath  = NULL;
  uuencodeext = NULL;

  mssdepth = 0;
  memset (&localenv, 0, sizeof (headers));
  memset (&sstate,   0, sizeof (scanstate));

  nofnum    = 0;
  mimseqno  = 0;
  lastvalid = 0;
  lastenc   = 0;
  uuyctr    = 0;


  for (aiter=toallocate; aiter->ptr; aiter++)
    *(aiter->ptr) = NULL;

  for (aiter=toallocate; aiter->ptr; aiter++) {
    if ((*(aiter->ptr) = (char *) malloc (aiter->size)) == NULL) {


      for (aiter=toallocate; aiter->ptr; aiter++) {
	_FP_free (*(aiter->ptr));
      }
      return UURET_NOMEM;
    }
  }


  UUInitConc ();

  return UURET_OK;
}
