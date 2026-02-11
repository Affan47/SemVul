parse_header(ESL_SQNCBI_DATA *ncbi, ESL_SQ *sq)
{
  int   size;
  int   status;
  void *tmp;

  unsigned char c;

  reset_header_values(ncbi);
  size  = ncbi->hoff - ncbi->roff;


  if (ncbi->hdr_alloced < size) {
    while (ncbi->hdr_alloced < size) ncbi->hdr_alloced += ncbi->hdr_alloced;
    ESL_RALLOC(ncbi->hdr_buf, tmp, sizeof(char) * ncbi->hdr_alloced);
  }
  if (fread(ncbi->hdr_buf, sizeof(char), size, ncbi->fpphr) != size) return eslEFORMAT;
  ncbi->hdr_ptr = ncbi->hdr_buf;


  if (parse_expect(ncbi, "\x30\x80", 2) != eslOK)             return eslEFORMAT;

  if (parse_peek(ncbi, &c) != eslOK)                          return eslEFORMAT;


  while (c != 0x00) {
    if ((status = parse_def_line(ncbi, sq)) != eslOK)         return status;

    if (parse_peek(ncbi, &c) != eslOK)                        return eslEFORMAT;
  }


  if (parse_expect(ncbi, "\x00\x00", 2) != eslOK)             return eslEFORMAT;

  return eslOK;
 ERROR:
  return eslEMEM;
}
