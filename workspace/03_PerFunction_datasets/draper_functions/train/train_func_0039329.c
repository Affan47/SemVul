gmon_io_read_32 (FILE *ifp, unsigned int *valp)
{
  char buf[4];

  if (fread (buf, 1, 4, ifp) != 4)
    return 1;
  *valp = bfd_get_32 (core_bfd, buf);
  return 0;
}
