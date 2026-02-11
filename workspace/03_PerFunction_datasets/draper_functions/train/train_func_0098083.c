loadmem(ESL_SQFILE *sqfp)
{
  void *tmp;
  int   n;
  int   status;

  ESL_SQASCII_DATA *ascii = &sqfp->data.ascii;

  if (ascii->do_buffer)
  {
      ascii->mpos = 0;
      ascii->mn   = 0;
  }
  else if (ascii->is_recording == TRUE)
  {
      if (ascii->mem == NULL) ascii->moff = ftello(ascii->fp);
      ESL_RALLOC(ascii->mem, tmp, sizeof(char) * (ascii->allocm + eslREADBUFSIZE));
      ascii->allocm += eslREADBUFSIZE;
      n = fread(ascii->mem + ascii->mpos, sizeof(char), eslREADBUFSIZE, ascii->fp);
      ascii->mn += n;
  }
  else
  {
      if (ascii->mem == NULL) {
        ESL_ALLOC(ascii->mem, sizeof(char) * eslREADBUFSIZE);
        ascii->allocm = eslREADBUFSIZE;
      }
      ascii->is_recording = -1;
      ascii->mpos = 0;
      ascii->moff = ftello(ascii->fp);
      n = fread(ascii->mem, sizeof(char), eslREADBUFSIZE, ascii->fp);
      ascii->mn   = n;
  }
  return (n == 0 ? eslEOF : eslOK);

 ERROR:
  return status;
}
