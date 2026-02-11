not_attribute(K a)
{
  I t=a->t, n=a->n;
  K z;
  if     (4==ABS(t)){U(z=newK(t,  n)) DO(n,if(!(kS(z)[i]=notsp(kS(a)[i]))){cd(z);R 0;}) }
  else if(2==ABS(t)){U(z=newK(t/2,n)) DO(n,kI(z)[i]= (0==kF(a)[i])?1:0;)}
  else if(1==ABS(t)){U(z=newK(t,  n)) DO(n,kI(z)[i]= (0==kI(a)[i])?1:0;)}
  else if(0==ABS(t)){U(z=newK(t,  n)) DO(n,if(!(kK(z)[i]=not_attribute(kK(a)[i]))){cd(z);R 0;})}
  else R TE;
  R z;
}
