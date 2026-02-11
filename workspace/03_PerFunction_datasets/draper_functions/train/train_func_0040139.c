esl_buffer_Read(ESL_BUFFER *bf, size_t nbytes, void *p)
{
  int status;

  if (bf->n - bf->pos < nbytes)
    {
      status = buffer_refill(bf, nbytes + bf->pagesize);
      if       (status == eslEOF)       return eslEOF;
      else if  (status != eslOK)        return status;
      else if  (bf->n-bf->pos < nbytes) return eslEOF;
    }

  memcpy(p, bf->mem+bf->pos, nbytes);
  bf->pos += nbytes;

  if ((status = buffer_refill(bf, 0)) != eslOK && status != eslEOF) return status;
  return eslOK;
}
