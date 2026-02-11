cnv_1bcas_into_garr(int32 n1bcas, struct conta_t *ca1bit_hd)
{
 register int32 gi;
 struct conta_t *cap, *cap2;
 int32 osize, nsize;
 struct gate_t *gp;
 struct net_t *dum_np;

 dum_np = NULL;

 __inst_mod->mod_1bcas  = TRUE;


 osize = __inst_mod->mgnum*sizeof(struct gate_t);
 nsize = osize + n1bcas*sizeof(struct gate_t);


 if (osize == 0) { gp = (struct gate_t *) __my_malloc(nsize); }
 else
  {
   gp = (struct gate_t *) __my_realloc((char *) __inst_mod->mgates,
    osize, nsize);
  }
 __inst_mod->mgates = gp;

 for (gi = 0; gi < __inst_mod->mgnum; gi++)
  {
   gp = &(__inst_mod->mgates[gi]);
   gp->gsym->el.egp = gp;
  }


 gi = __inst_mod->mgnum;
 __inst_mod->mgnum += n1bcas;
 for (cap = ca1bit_hd; cap != NULL; gi++)
  {
   gp = &(__inst_mod->mgates[gi]);
   convert_1bca_togate(gp, cap);


   gp->gsym = cap->casym;
   gp->gsym->el.egp = gp;
   gp->gsym->sytyp = SYM_PRIM;
   if (!chk_gate_source(gp, gp->gpins[0], FALSE, FALSE, &dum_np))
    {
     __free_xtree(gp->gpins[0]);
     set_unc_gateterm(gp, 0);
    }

   cap2 = cap->pbcau.canxt;

   __my_free((char *) cap, sizeof(struct conta_t));
   cap = cap2;
  }
}
