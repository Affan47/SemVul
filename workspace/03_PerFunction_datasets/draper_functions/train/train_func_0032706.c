scanMonad(K a, V *p, K b)
{
  K u=enlist(b),v,w,c=0,d;I flag=0;
  U(u);

  I useN=0,n=0,useB=0;
  if(a) if(1 == a->t){useN=1; n=*kI(a);}else if(7==a->t)useB=1;
  P(n < 0,IE)

  if(useN) DO(n, U(v=reverse(u)) d=first(v); cd(v); c=dv_ex(0,p-1,d); cd(d); U(c) U(v=enlist(c)) cd(c); u=join(w=u,v); cd(w); cd(v); U(u))
  else if(useB)
  {
    I t;
    do
    {
      U(v=reverse(u))
      d=first(v); cd(v);
      K*aa=&a;
      K g=dv_ex(0,&aa,d); U(g)
      t=(1==g->t && *kI(g));
      cd(g);
      if(!t){cd(d); break;}
      c=dv_ex(0,p-1,d); cd(d);
      U(c) U(v=enlist(c)) cd(c);
      u=join(w=u,v); cd(w); cd(v); U(u)
    }while(1);
  }
  else while(1)
  {
    d=first(v=reverse(u));cd(v);
    if(matchI(b,c) || matchI(c,d))flag=1;
    if(!flag && c)
    {
      u=join(v=u,w=enlist(c));
      cd(v);cd(w);cd(d);
      d=c;
    }
    if(interrupted){interrupted=0;R BE;}
    if(flag){cd(c);cd(d);break;}
    c=dv_ex(0,p-1,d);cd(d);
  }
  R u;
}
