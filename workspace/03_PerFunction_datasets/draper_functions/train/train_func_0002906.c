__exec_qc_deassign(struct st_t *stp, int32 is_force)
{
 register struct expr_t *catndp;
 struct expr_t *lhsx, *catlhsx;


 lhsx = stp->st.sqcdea.qcdalhs;

 if (lhsx->optyp != LCB)
  {
   if (is_force) do_qc_regrelease(lhsx);
   else do_qc_deassign(lhsx);
  }
 else
  {

   for (catndp = lhsx->ru.x; catndp != NULL; catndp = catndp->ru.x)
    {
     catlhsx = catndp->lu.x;
     if (is_force) do_qc_regrelease(catlhsx);
     else do_qc_deassign(catlhsx);
    }
  }
}
