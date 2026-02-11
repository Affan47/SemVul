get_varorparam_val(struct h_t *hp, p_vpi_value value_p)
{
 register struct net_t *np;
 register struct xstk_t *xsp;
 byte *sbp;
 struct xstk_t *xsp2;


 np = hp->hrec->hu.hnp;

 if (value_p->format == vpiObjTypeVal)
  correct_objtypval(value_p, np->ntyp, np->n_isavec, np->n_stren, FALSE);


 if (value_p->format != vpiStrengthVal)
  {
   push_xstk_(xsp, np->nwid);
   __ld_wire_val(xsp->ap, xsp->bp, np);
   fill_valuep(value_p, xsp, np->ntyp, np->nwid);
   __pop_xstk();
   return;
  }


 if (np->n_stren)
  {
   get_stwire_addr_(sbp, np);
   if (np->nwid == 1) stscal_fill_valuep(value_p, sbp, 0);
   else stvec_fill_valuep(value_p, sbp, np->nwid);
   return;
  }

 push_xstk_(xsp, np->nwid);
 __ld_wire_val(xsp->ap, xsp->bp, np);

 push_xstk_(xsp2, 4*np->nwid);
 sbp = (byte *) xsp2->ap;

 __st_standval(sbp, xsp, ST_STRVAL);
 if (np->nwid == 1) stscal_fill_valuep(value_p, sbp, 0);
 else stvec_fill_valuep(value_p, sbp, np->nwid);
 __pop_xstk();
 __pop_xstk();
}
