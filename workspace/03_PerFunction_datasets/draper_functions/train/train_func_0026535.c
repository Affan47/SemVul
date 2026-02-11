single_normal_cm_class_equivalence( tparm_DS tparm1,tparm_DS tparm2, double sigma_ratio)
{
   struct sn_cm_param *sn1 = &(tparm1->ptype.sn_cm);
   struct sn_cm_param *sn2 = &(tparm2->ptype.sn_cm);

   if (fabs((double) (sn1->mean - sn2->mean)) <
       (sigma_ratio * (double) min(sn1->sigma, sn2->sigma)))
     return(TRUE);
   else
     return(FALSE);
}
