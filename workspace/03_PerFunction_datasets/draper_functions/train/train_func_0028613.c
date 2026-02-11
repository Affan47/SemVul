compress_to_file_mmap(FILE *fout, FILE *fin)
{
  int len, ifd = fileno(fin);
  char *buf;
  struct stat st;


  if (fstat(ifd, &st) < 0)
    return COMPF_ERROR;
  if (st.st_size <= 0)
    return COMPF_ERROR;


  buf = mmap(0, st.st_size, PROT_READ, MAP_SHARED, ifd, 0);
  if (buf < 0)
    return COMPF_ERROR;


  len = gzwrite(fout, buf, st.st_size);
  if (len != (int) st.st_size)
    return COMPF_ERROR;

  munmap(buf, st.st_size);
  fclose(fin);
  if (gzclose(fout) != Z_OK)
    return COMPF_ERROR;
  return COMPF_SUCCESS;
}
