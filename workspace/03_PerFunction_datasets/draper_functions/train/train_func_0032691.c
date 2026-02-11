xtrct_param(struct itree_t **itp2, char *pnam, struct itree_t *itp)
{
 int32 i1, i2;
 struct expr_t *glbndp;
 struct sy_t *tailsyp;
 char s1[IDLEN], s2[RECLEN];

 if (itp == NULL)
  {
   __pv_ferr(1201,
    "SDF (LABEL hierarchical parameter reference %s illegal with (INSTANCE *) form - type unknown",
    __token);
   return(FALSE);
  }


 if (!__id_qualpath)
  {

   if (!chkcnv_sdfid(pnam, &i1, &i2, __token, FALSE))
    {
     __pv_ferr(1344, "(LABEL %s illegal Verilog parameter name", __token);
     return(FALSE);
    }
   *itp2 = itp;
   return(TRUE);
  }


 if (!chkcnv_sdfpath(s1, &i1, &i2, __token, FALSE))
  {
   __pv_ferr(1348,
    "(LABEL hierarchical parameter name %s illegal Verilog global reference",
    __token);
   return(FALSE);
  }


 __push_wrkitstk(__sdf_mdp, 0);
 if ((glbndp = __glbnam_to_expr(s1)) == NULL)
  {
   __pop_wrkitstk();
   return(FALSE);
  }


 *itp2 = get_sdfdownrel_itp(glbndp, itp, &tailsyp, s2);

 __free_xtree(glbndp);
 __pop_itstk();
 if (*itp2 == NULL)
  {
   __pv_ferr(1388,
    "(LABEL form qualified path %s.%s name illegal in context %s: %s",
    s1, pnam, get_sdfcntxtnam(__xs, itp), s2);
   return(FALSE);
  }
 if (tailsyp->sytyp != SYM_N || !tailsyp->el.enp->n_isaparam)
  {
   __pv_ferr(1201,
    "SDF (LABEL hierarchical parameter reference %s illegal - %s not a parameter",
    __token, tailsyp->synam);
   return(FALSE);
  }
 strcpy(pnam, tailsyp->synam);
 return(TRUE);
}
