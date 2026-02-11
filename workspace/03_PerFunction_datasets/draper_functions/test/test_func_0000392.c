popen_charvec(C *cmd)
{
  FILE *f; K z; K l; S s=0; I n=0;
  f=popen(cmd,"r");
  P(!f,_n())
  z=newK(0,0);
  while (getline_(&s, &n, f) >= 0)
  { l=newK(-3,n-1);
    strncpy(kC(l),s,n-1);
    kap(&z,l);
  }
  if(s)free(s);
  pclose(f);
  R z;
}
