__narrow_sizchg(register struct xstk_t *xsp, int32 nblen)
{
 register int32 wi;
 register word32 *wpnb, *wpob;
 int32 nwlen, nubits, stkwlen;


 nwlen = wlen_(nblen);
 nubits = ubits_(nblen);
 stkwlen = wlen_(xsp->xslen);

 if (stkwlen == nwlen)
  {
   xsp->ap[nwlen - 1] &= __masktab[nubits];
   xsp->bp[nwlen - 1] &= __masktab[nubits];
   xsp->xslen = nblen;
   return;
  }


 wpnb = &(xsp->ap[nwlen]);
 wpob = xsp->bp;


 for (wi = 0; wi < nwlen; wi++) wpnb[wi] = wpob[wi];
 xsp->bp = wpnb;
 xsp->ap[nwlen - 1] &= __masktab[nubits];
 xsp->bp[nwlen - 1] &= __masktab[nubits];
 xsp->xslen = nblen;
}
