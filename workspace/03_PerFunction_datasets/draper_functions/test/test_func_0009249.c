ep_dep(A a)
{
  V v,vl; I *l,n=0,err; A result;
  NDC1(a);v=avlu(a,&err);
  if (!v) if(err){ERROUT(ERR_DOMAIN);}else R 0;
  for(l=v->l;l;l=(I*)*l)++n;
  result=gv(Et, n); n=0;
  for(l=v->l;l;l=(I*)*l)
    {vl=(V)l[1];result->p[n++]=MS(symjoin(vl->cx->s,vl->s));}
  R result;
}
