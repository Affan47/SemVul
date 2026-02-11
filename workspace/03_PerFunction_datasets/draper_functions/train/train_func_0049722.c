ReadByte(unsigned char **p,size_t *length)
{
  unsigned char
    c;

  if (*length < 1)
    return(0xff);
  c=(*(*p)++);
  (*length)--;
  return(c);
}
