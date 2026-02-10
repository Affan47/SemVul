read_nres_amino(ESL_SQFILE *sqfp, ESL_SQ *sq, int len, uint64_t *nres)
{
  int     inx;
  int     off;
  int     size;

  char   *ptr;

  ESL_SQNCBI_DATA *ncbi = &sqfp->data.ncbi;

  if (ncbi->index >= ncbi->num_seq) return eslEOF;


  if (ncbi->seq_L == -1) ncbi->seq_L = sq->eoff - sq->doff - 1;


  if (sq->start + sq->n > ncbi->seq_L) {
    if (nres != NULL) *nres = 0;
    sq->L = ncbi->seq_L;
    return eslEOD;
  }


  ptr = (sq->dsq != NULL) ? (char *)sq->dsq + 1 : sq->seq;
  ptr += sq->n;


  off   = sq->doff + sq->start + sq->n - 1;


  size = ncbi->seq_L - (sq->start + sq->n - 1);
  size = (size > len) ? len : size;


  if (fseek(ncbi->fppsq, off, SEEK_SET) != 0) return eslESYS;
  if (fread(ptr, sizeof(char), size, ncbi->fppsq) != size) return eslEFORMAT;


  for (inx = 0; inx < size; ++inx) {
    *ptr = sqfp->inmap[(int) *ptr];
    if (sq->dsq == NULL) *ptr = ncbi->alphasym[(int) *ptr];
    ++ptr;
  }

  *ptr = (sq->dsq == NULL) ? '\0' : eslDSQ_SENTINEL;

  sq->n = sq->n + size;

  if (nres != NULL) *nres = size;

  return eslOK;
}
