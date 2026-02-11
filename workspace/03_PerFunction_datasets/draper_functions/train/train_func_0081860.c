explintyl(l0,l1,cf,I,p)
double l0, l1, *cf, *I;
INT p;
{ INT i;
  double c;
  explint1(l0,l1,cf,I,p+8);
  c = cf[2];
  for (i=0; i<p; i++)
    I[i] = (((I[i+8]*c/4+I[i+6])*c/3+I[i+4])*c/2+I[i+2])*c+I[i];
}
