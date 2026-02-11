chk_circular_qc_stmt(struct st_t *stp)
{
 register struct expr_t *lhsx, *rhsx;
 int32 qctyp;
 struct expr_t *catndp, *catelx, *lhsx2;
 struct net_t *np;
 char s1[RECLEN];

 lhsx = stp->st.sqca->qclhsx;
 rhsx = stp->st.sqca->qcrhsx;
 qctyp =   stp->st.sqca->qcatyp;
 if (lhsx->optyp == LCB)
  {
   for (catndp = lhsx->ru.x; catndp != NULL; catndp = catndp->ru.x)
    {
     catelx = __get_lvalue_idndp(catndp->lu.x);

     if (catelx->optyp != ID && catelx->optyp != GLBREF)
      __misc_terr(__FILE__, __LINE__);

     np = catelx->lu.sy->el.enp;

     if (rhs_expr_has_net(rhsx, np))
      {
       if (qctyp != FORCE && qctyp != RELEASE)
        {
         __sgferr(3409,
           "net %s in concatenate on both left and right hand sides of QC %s - illegal infinite loop",
           np->nsym->synam, __to_qctyp(s1, qctyp));
         return;
        }
      }
    }
   return;
  }
 lhsx2 = __get_lvalue_idndp(lhsx);

 if (lhsx2->optyp != ID && lhsx2->optyp != GLBREF)
  __misc_terr(__FILE__, __LINE__);

 np = lhsx2->lu.sy->el.enp;
 if (rhs_expr_has_net(rhsx, np))
  {
   __sgferr(3409,
    "net %s on both left and right hand sides of QC %s - illegal infinite loop",
    np->nsym->synam, __to_qctyp(s1, qctyp));
  }
}
