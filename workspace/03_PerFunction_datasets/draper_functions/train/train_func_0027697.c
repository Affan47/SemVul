bld_gstate(void)
{
 register int32 gi;
 struct mod_t *mdp;
 struct gate_t *gp;


 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   __push_wrkitstk(mdp, 0);

   for (gi = 0; gi < mdp->mgnum; gi++)
    {
     gp = &(mdp->mgates[gi]);


     if (gp->g_class == GC_PULL || gp->g_class == GC_TRAN) continue;


     if (gp->g_class != GC_TRANIF && gp->gpins[0]->optyp == OPEMPTY)
      continue;

     if (gp->g_du.pdels == NULL)
      { gp->g_du.d1v = NULL; gp->g_delrep = DT_NONE; }
     else
      {
       add_gatedel_pnp(gp, gp->g_du.pdels);
       __prep_delay(gp, gp->g_du.pdels, FALSE, FALSE, "primitive delay",
        FALSE, gp->gsym, FALSE);
       if (__nd_neg_del_warn)
        {
         __gferr(972, gp->gsym->syfnam_ind, gp->gsym->sylin_cnt,
          "gate %s delay negative (0 used)", gp->gsym->synam);
         __nd_neg_del_warn = FALSE;
        }
      }

     if (__rm_gate_pnd0s)
      {
       if (__chk_0del(gp->g_delrep, gp->g_du, mdp) == DBAD_0)
        {
         __num_rem_gate_pnd0s++;
         __num_flat_rem_gate_pnd0s += mdp->flatinum;
         __free_del(gp->g_du, gp->g_delrep, mdp->flatinum);
         gp->g_du.d1v = NULL;
         gp->g_delrep = DT_NONE;
        }
      }

     alloc_gstate(gp, mdp->flatinum);
    }
   __pop_wrkitstk();
  }
}
