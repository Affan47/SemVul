af(I n){
  jmp_buf b;
  A fnc=(A)*Y;
  I i=0,*k,t=0,*x,z=0,h=fnc->t==Xt;
  jmptype j;
  I *d;
  if(h)
  {
    d=fnc->d;
    if(QN(*d)){
      EQ(1,n!=2&&n!=3?(q=5,0):
	 (z=n>2?Y[2]:0,fnc->r>2?rk(d[1],(A)d[2],(A)Y[1],(A)z):
	  ea(d[1],(A)Y[1],(A)z))
	 );
      R z;
    }
    for(h=i=fnc->r;i--;*--Y=ic((A)d[i]));L0:fnc=(A)*Y;
  }
  if(fnc->t<=Xt)q=14;
  else if(Y-K<30)q=3;
  else if(n+h!=fnc->r)q=5;
  else if(!*fnc->p)q=4;
  else
  {
    CX c=Cx;
    x=X,X=Y,j=J,k=K,*++K=(I)fnc;
    DO(fnc->n-1,*--Y=0);
    FIN;
    if(z=setjmp(J=b))
    {
      if(Cx=c,z==-3||z==-1)
	{
	  FOUT(2);
	  if(z==-3)longjmp(j,-3);
	}
      else
	{
	  if(Glbrtn)
	    z = (I)Glbrtn ;
	}
    }
    else z=ev(*fnc->p);
    for(;Y<X;dc((A)(*Y++)));
    K=k,J=j,X=x;
  }
  if(q)if(z=aplus_err(q,fnc),!z)goto L0;
  DO(h,dc((A)(*Y++)))FOUT(1);
  R z;
}
