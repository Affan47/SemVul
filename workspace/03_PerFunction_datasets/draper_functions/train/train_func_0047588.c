ep_flat( a) register A a;
{
  A z;
  I n, type=-1;
  n=flat_onepass(a, &type);
  if (q) R 0;
  if (-1==type) type=Et;
  z=gv((Xt==type)?Et:type,n);
  flat_twopass(a,type,(C *)z->p);
  if (Ct==type) ((C *)(z->p))[z->n]='\0';
  R z;
}
