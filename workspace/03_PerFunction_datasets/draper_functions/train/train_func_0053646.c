compare_files2(File fd, const char* filename2)
{
  int error= RESULT_OK;
  File fd2;
  size_t len, len2;
  char buff[512], buff2[512];

  if ((fd2= my_open(filename2, O_RDONLY, MYF(0))) < 0)
  {
    my_close(fd, MYF(0));
    die("Failed to open second file: '%s'", filename2);
  }
  while((len= my_read(fd, (uchar*)&buff,
                      sizeof(buff), MYF(0))) > 0)
  {
    if ((len2= my_read(fd2, (uchar*)&buff2,
                       sizeof(buff2), MYF(0))) < len)
    {

      error= RESULT_LENGTH_MISMATCH;
      break;
    }
    if (len2 > len)
    {

      error= RESULT_LENGTH_MISMATCH;
      break;
    }
    if ((memcmp(buff, buff2, len)))
    {

      error= RESULT_CONTENT_MISMATCH;
      break;
    }
  }
  if (!error && my_read(fd2, (uchar*)&buff2,
                        sizeof(buff2), MYF(0)) > 0)
  {

    error= RESULT_LENGTH_MISMATCH;
  }

  my_close(fd2, MYF(0));

  return error;
}
