conv_line_tostmt(struct mod_t *in_mdp,
 struct task_t *in_tskp, int32 ifi, int32 lini)
{
 register struct ialst_t *ialp;
 struct st_t *stp, *stp2;
 struct incloc_t *ilp;
 int32 st_ifi, st_lini, ifi2, lini2;


 if ((ilp = find2_incloc(ifi)) != NULL)
  { ifi2 = ilp->incfrom_fnind; lini2 = ilp->incfrom_lcnt; }
 else { ifi2 = ifi; lini2 = lini; }


 if (in_tskp != NULL)
  {
   stp = in_tskp->tskst;

   if (stp == NULL) __misc_terr(__FILE__, __LINE__);
   st_ifi = (int32) stp->stfnam_ind;
   st_lini = stp->stlin_cnt;

   if (ifi2 <= st_ifi && lini2 <= st_lini) return(stp);


   if ((stp2 = find_lstofsts_stp(stp, ifi, lini)) != NULL) return(stp2);


   return(__blklast_stp);
  }


 for (ialp = in_mdp->ialst; ialp != NULL; ialp = ialp->ialnxt)
  {
   stp = ialp->iastp;

   if (ifi2 < ialp->ia_first_ifi || (ifi2 == ialp->ia_first_ifi
    && lini2 < ialp->ia_first_lini)) continue;

   if (ifi2 > (int32) ialp->ia_last_ifi || (ifi2 == ialp->ia_last_ifi
    && lini2 > ialp->ia_last_lini)) continue;


   if ((stp2 = find_lstofsts_stp(stp, ifi, lini)) != NULL) return(stp2);

   return(__blklast_stp);
  }
 return(NULL);
}
