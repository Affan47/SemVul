cmp_xform_contas(void)
{
 register int32 bi;
 register struct conta_t *cap, *pbcap;
 int32 cai;

 for (cap = &(__inst_mod->mcas[0]), cai = 0; cai < __inst_mod->mcanum;
  cai++, cap++)
  {

   cmp_xform_delay(cap->ca_delrep, cap->ca_du);

   cap->lhsx = mv1_expr_totab(cap->lhsx);
   cap->rhsx = mv1_expr_totab(cap->rhsx);
   if (cap->ca_pb_sim)
    {
     for (bi = 0; bi < cap->lhsx->szu.xclen; bi++)
      {
       pbcap = &(cap->pbcau.pbcaps[bi]);
       pbcap->lhsx = mv1_expr_totab(pbcap->lhsx);
       pbcap->rhsx = mv1_expr_totab(pbcap->rhsx);
      }
    }
  }
}
