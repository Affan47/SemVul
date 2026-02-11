esl_ssi_FindSubseq(ESL_SSI *ssi, const char *key, int64_t requested_start,
		   uint16_t *ret_fh, off_t *ret_roff, off_t *ret_doff, int64_t *ret_L, int64_t *ret_actual_start)
{
  int      status;
  uint64_t r, b, i, l;


  if ((status = esl_ssi_FindName(ssi, key, ret_fh, ret_roff, ret_doff, ret_L)) != eslOK) goto ERROR;
  if (requested_start < 0 || requested_start > *ret_L) { status = eslERANGE; goto ERROR; }


  if (*ret_doff == 0 || ! (ssi->fileflags[*ret_fh] & eslSSI_FASTSUBSEQ))
    {
      *ret_actual_start = 1;
      return eslOK;
    }


  r = ssi->rpl[*ret_fh];
  b = ssi->bpl[*ret_fh];
  i = requested_start;
  l = (i-1)/r;
  if (r == 0 || b == 0) { status = eslEINVAL; goto ERROR; }


  if (b == r+1)
    {
      *ret_doff        += l*b + (i-1)%r;
      *ret_actual_start = requested_start;
    }


  else
    {
      *ret_doff         += l*b;
      *ret_actual_start = 1 + l*r;
    }
  return eslOK;

 ERROR:
  *ret_fh           = 0;
  *ret_roff         = 0;
  *ret_doff         = 0;
  *ret_L            = 0;
  *ret_actual_start = 0;
  return status;
}
