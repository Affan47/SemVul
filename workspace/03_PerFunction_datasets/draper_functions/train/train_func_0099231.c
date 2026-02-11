__sizchg_widen(register struct xstk_t *xsp, int32 nblen)
{
 register int32 wi;
 register word32 *wpna, *wpnb, *wpob;
 int32 nwlen, nubits, stkwlen, xtrabits;


 if (nblen <= WBITS) { xsp->xslen = nblen; return; }
 nwlen = wlen_(nblen);

 stkwlen = wlen_(xsp->xslen);
 if (nwlen == stkwlen) { xsp->xslen = nblen; return; }
 nubits = ubits_(nblen);

 if (nwlen > xsp->xsawlen)
  {


   wpna = (word32 *) __my_malloc(2*WRDBYTES*nwlen);
   memcpy(wpna, xsp->ap, WRDBYTES*xsp->xsawlen);


   wpnb = &(wpna[nwlen]);
   memcpy(wpnb, xsp->bp, WRDBYTES*xsp->xsawlen);

   __my_free((char *) xsp->ap, 2*WRDBYTES*xsp->xsawlen);
   xsp->ap = wpna;
   xsp->bp = wpnb;
   xsp->xsawlen = nwlen;
  }
 else
  {

   wpob = xsp->bp;

   wpnb = &(xsp->ap[nwlen]);

   for (wi = stkwlen - 1; wi >= 0; wi--) wpnb[wi] = wpob[wi];
   xsp->bp = wpnb;
  }

 xtrabits = (nblen - WBITS*stkwlen);
 zero_allbits_(&(xsp->ap[stkwlen]), xtrabits);
 zero_allbits_(&(xsp->bp[stkwlen]), xtrabits);
 xsp->xslen = nblen;
}
