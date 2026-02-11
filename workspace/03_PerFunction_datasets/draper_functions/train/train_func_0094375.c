ep_get(A var,A att){V v;NDC2(var,att);v=av(var);
 if(!v||!sym(att)||att->n!=1)ERROUT(ERR_DOMAIN);R(A)ep_gatt(v,XS(*att->p));}
