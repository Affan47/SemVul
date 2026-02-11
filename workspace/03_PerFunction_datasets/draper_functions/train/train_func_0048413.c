get_floats(Sock *sock,double *vals,int num)
{
  int i;
  for(i=0; i<num; i++)
    *vals++ = get_float(sock);
  return 0;
}
