tf_propagatep(int32 pnum)
{
 register int32 wi;
 register struct xstk_t *xsp;
 register struct t_vecval *vecp;
 register struct t_tfexprinfo *xpinfo;
 int32 rv;
 double d1;
 struct tfarg_t *tfap;
 struct expr_t *lhsxp;

 if (__tfrec == NULL)
  {
   rv = bad_notfcontext_err("tf_propagatep");

   if (rv == TF_NULLPARAM) return(1); else return(0);
  }
 tfap = &(__tfrec->tfargs[pnum]);
 if (pnum < 1 || pnum >= __tfrec->tfanump1) return(1);


 xpinfo = (struct t_tfexprinfo *) tfap->sav_xinfos[__inum];
 if (xpinfo == NULL) return(1);

 if (xpinfo->expr_type == TF_READONLY
  || xpinfo->expr_type == TF_READONLYREAL
  || xpinfo->expr_type == TF_STRING
  || xpinfo->expr_type == TF_NULLPARAM)
  {
   __sgferr(1280,
    "tf_propagatep saved expression illegal - expressions not writeable");
   return(1);
  }
 lhsxp = tfap->arg.axp;
 if (lhsxp->x_stren)
  {
   __sgferr(1212,
    "tf_propagatep of strength expression illegal - tf_ does not store strength");
   return(1);
  }


 if (xpinfo->expr_type == TF_READWRITEREAL)
  {
   d1 = xpinfo->real_value;
   push_xstk_(xsp, REALBITS);
   memcpy(xsp->ap, &d1, sizeof(double));
  }
 else
  {


   push_xstk_(xsp, xpinfo->expr_ngroups*WBITS);
   vecp = xpinfo->expr_value_p;
   for (wi = 0; wi < xpinfo->expr_ngroups; wi++)
    {
     xsp->ap[wi] = (word32) vecp[wi].avalbits;
     xsp->bp[wi] = (word32) vecp[wi].bvalbits;
    }
  }
 exec_tfarg_assign(tfap, lhsxp, xsp->ap, xsp->bp);
 __pop_xstk();
 return(0);
}
