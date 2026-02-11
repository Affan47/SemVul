__to_wrange(char *s, struct net_t *np)
{
 int32 r1, r2;

 if (np->n_isavec)
  {
   if (np->nrngrep == NX_CT)
    __msgtox_wrange(s, np->nu.ct->nx1, np->nu.ct->nx2);
   else
    {


     __getwir_range(np, &r1, &r2);
     sprintf(s, "[%d:%d]", r1, r2);
    }
  }
 else strcpy(s, "");
 return(s);
}
