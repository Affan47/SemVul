unix_fstat(value fd)
{
  int ret;
  struct stat buf;
  ret = fstat(Int_val(fd), &buf);
  if (ret == -1) uerror("fstat", Nothing);
  if (buf.st_size > Max_long && (buf.st_mode & S_IFMT) == S_IFREG)
    unix_error(EOVERFLOW, "fstat", Nothing);
  return stat_aux(0, &buf);
}
