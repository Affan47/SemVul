sqascii_IsRewindable(const ESL_SQFILE *sqfp)
{
  if (sqfp->data.ascii.do_gzip  == TRUE) return FALSE;
  if (sqfp->data.ascii.do_stdin == TRUE) return FALSE;
  return TRUE;
}
