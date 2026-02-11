decoded_number_xfmt(char **buf)
{
  unsigned char c1;

  c1=(*buf)[0];
  if(c1<'!' || c1>'~')
    return(-32768);
  (*buf)++;

  return(c1=='~'?decoded_number_basefmt(buf):(c1-'!')-46);
}
