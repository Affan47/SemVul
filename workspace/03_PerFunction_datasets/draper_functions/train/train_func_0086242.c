cnt_nplstels(register struct net_pin_t *npp)
{
 int32 i;

 for (i = 0; npp != NULL; npp = npp->npnxt)
  {
   if (npp->npntyp != NP_MIPD_NCHG) i++;
  }
 return(i);
}
