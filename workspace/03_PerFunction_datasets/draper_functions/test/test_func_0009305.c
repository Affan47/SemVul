gribrec_len(int b1, int b2, int b3)
{
  int gribsize;

  gribsize = (1-(int) ((unsigned) (b1&128) >> 6)) * (int) (((b1&127) << 16)+(b2<<8) + b3);


  if ( gribsize < 0 ) gribsize *= (-120);

  return (gribsize);
}
