read_byte (void)
{
  int b = get_byte ();
  if (b < 0)
    gzip_error ("invalid compressed data -- unexpected end of file");
  return b;
}
