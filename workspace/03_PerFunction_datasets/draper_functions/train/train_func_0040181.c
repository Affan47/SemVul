mod(K a, K b)
{
  I at=a->t, an=a->n, bt=b->t;
  P(ABS(at) > 2,TE)

  I t=(0==at)?0:MAX(ABS(at),ABS(bt))*(at>0?1:-1);

  K z=newK(t,an); U(z)
  I c,d,e; F f,g,h;
  #define FMOD h=g?f-g*floor(f/g):f; kF(z)[i]=h;
  if     (2==ABS(at) && 2==bt) { g=*kF(b); DO(an, f=kF(a)[i]; FMOD) }
  else if(2==ABS(at) && 1==bt) { g=*kI(b); DO(an, f=kF(a)[i]; FMOD) }
  else if(1==ABS(at) && 2==bt) { g=*kF(b); DO(an, f=kI(a)[i]; FMOD) }
  else if(1==ABS(at) && 1==bt)
  {
    d=*kI(b);
    if(d>0) DO(an, c=kI(a)[i]; e=d?c-d*(c/d):c; kI(z)[i]=e)
    else    DO(an, c=kI(a)[i]; e=d?c-d*floor(c/(F)d):c; kI(z)[i]=e)

  }
  else if(0==at) DO(an, if(!(kK(z)[i]=mod(kK(a)[i],b))){cd(z);R 0;})
  R z;
}
