__pth_schd_allofwire(struct net_t *np, register word32 *ap,
 register word32 *bp, int32 blen)
{
 register int32 bi;
 register word32 aval, bval;
 word32 av, bv;

 if (!np->n_isavec)
  {
   aval = ap[0] | (bp[0] << 1);

   __ld_wire_val(&av, &bv, np);
   av |= (bv << 1);

   schd_1pthwirebit(np, 0, aval, av);
   return;
  }


 if (blen >= np->nwid)
  {
   for (bi = 0; bi < blen; bi++)
    {
     aval = rhsbsel_(ap, bi);
     bval = rhsbsel_(bp, bi);
     aval |= (bval << 1);
     __ld_bit(&av, &bv, np, bi);
     schd_1pthwirebit(np, bi, aval, (av | (bv << 1)));
    }
   return;
  }

 for (bi = 0; bi < blen; bi++)
  {
   aval = rhsbsel_(ap, bi);
   bval = rhsbsel_(bp, bi);
   aval |= (bval << 1);
   __ld_bit(&av, &bv, np, bi);
   schd_1pthwirebit(np, bi, aval, (av | (bv << 1)));
  }
 for (bi = blen; bi < np->nwid; bi++)
  {
   __ld_bit(&av, &bv, np, bi);
   schd_1pthwirebit(np, bi, (word32) 2, (av | (bv << 1)));
  }
}
