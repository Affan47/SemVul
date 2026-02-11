ep_ex(A a)
{
  V v;I err;
  I emptyV() ;
  NDC1(a);v=avlu(a,&err);
  if(!v)if(err){ERROUT(ERR_DOMAIN);}else R 1;
  R(qv0(v)&&!v->o)?(emptyV(v),0):1;
}
