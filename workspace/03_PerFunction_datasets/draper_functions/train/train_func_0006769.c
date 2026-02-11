chk_pli_arglist(register struct expr_t *argxp, int32 stfnum)
{
 int32 lhstyp;
 struct expr_t *xp;
 struct sy_t *syp;


 for (; argxp != NULL; argxp = argxp->ru.x)
  {
   xp = argxp->lu.x;


   if (xp->optyp == GLBREF)
    {
     syp = xp->lu.sy;

     if (syp->sytyp == SYM_M) continue;

     if (syp->sytyp == SYM_I || syp->sytyp == SYM_TSK
      || syp->sytyp == SYM_LB) continue;


     if (syp->sytyp == SYM_F) __misc_terr(__FILE__, __LINE__);


    }


   if (stfnum > __last_veriusertf)
    {
     if ((xp->optyp == ID || xp->optyp == GLBREF) && xp->lu.sy->sytyp == SYM_N
      && xp->lu.sy->el.enp->n_isarr) continue;
    }

   if (tfexpr_isrw(xp))
    {
     if (lhs_is_decl(xp)) lhstyp = LHS_DECL; else lhstyp = LHS_PROC;
     __chk_lhsexpr(xp, lhstyp);
     xp->tf_isrw = TRUE;
    }
   else __chk_rhsexpr(xp, 0);
  }
}
