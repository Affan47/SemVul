ee(E expr)
{
  I z = 0,i,n,fnc;
	fnc = expr->f;
  if(QN(fnc))
    R(*PN[U(fnc)])(expr);
  for(i=n=expr->n;i;*--Y=z)
  {
    z=expr->a[--i];
    EV(z);
  }
  EV(fnc);
  if(QA(fnc))
  {
    ++n;
    *--Y=fnc;
    if(((A)fnc)->t>Xt+1)
      R z=(I)ga(Xt,n,0L,Y),Y+=n,z;
    z=af(n);
  }
  else
  {
    i=U(fnc);
    EQ(0,QX(fnc)?(i?PX(i,n):xin((A)*Y,n-1,(A)0)):
       n==2?(*P2[i])(*Y,Y[1],i):(*P1[i])(*Y,i));
  }
  DO(n,dc((A)(*Y++)));
  R z;
}
