add_write(File fptr, const char *buf, uint len)
{
  uint ret_code= mysql_file_write(fptr, (const uchar*)buf, len, MYF(MY_FNABP));

  if (likely(ret_code == 0))
    return 0;
  else
    return 1;
}
