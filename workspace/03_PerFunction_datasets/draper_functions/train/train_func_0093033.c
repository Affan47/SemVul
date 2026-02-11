qp_char(unsigned char c1, unsigned char c2, char *c_out)
{
  c1 = unhex(c1);
  c2 = unhex(c2);

  if ((c1 > 15) || (c2 > 15))
    return 1;
  else {
    *c_out = 16*c1+c2;
    return 0;
  }
}
