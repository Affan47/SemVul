__chg_st_val(register struct net_t *np, word32 *rgap, word32 *rgbp)
{
 register word32 *dwp;
 int32 wlen;
 byte *netsbp, *newsbp;

 switch ((byte) np->srep) {
  case SR_SCAL:
   chg_st_scalval_(np->nva.bp, rgap[0], rgbp[0]);
   break;
  case SR_VEC:
   wlen = wlen_(np->nwid);
   dwp = &(np->nva.wp[2*wlen*__inum]);
   chg_st_vecval(dwp, np->nwid, rgap, rgbp);
   break;
  case SR_SVEC:

   netsbp = &(np->nva.bp[np->nwid*__inum]);
   newsbp = (byte *) rgap;
   if (memcmp(netsbp, newsbp, np->nwid) != 0)
    {

     memcpy(netsbp, newsbp, np->nwid);
     __lhs_changed = TRUE;
    }
   break;
  case SR_SSCAL:
   netsbp = &(np->nva.bp[__inum]);
   newsbp = (byte *) rgap;
   if (*netsbp != *newsbp) { *netsbp = *newsbp; __lhs_changed = TRUE; }
   break;
  default: __case_terr(__FILE__, __LINE__); return;
 }
 if (__lhs_changed) record_nchg_(np);
}
