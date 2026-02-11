u_rs(C *v,I i)
{
  I t=0;
  C c=*s;
  *s=0;
  if(i&&(*v=='\312'||(t=aplus_pi(v))))
  {
    if(c=='/'||c=='\\'||c=='\256'||c=='.'&&!isan(s[1]))
    {
      *s++=c;
      if(c=='.'&&*s&&!ispu(*s)&&!issp(*s))++s;
      c=*s,*s=0,t=aplus_pi(v);
    }
    if(!t)trr(2,v,s,c);
  }
  else
  {
    if(i==1)trr(2,v,s,c);
    t=MS(si(v));
  }
  R *s=c,t;
}
