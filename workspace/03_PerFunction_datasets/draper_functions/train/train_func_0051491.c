out_char (int c)
{
  char bytes[1];

  bytes[0] = (char)c;


  if (full_write (out_fd, bytes, 1) < 1)
    out_error ();
  return 0;
}
