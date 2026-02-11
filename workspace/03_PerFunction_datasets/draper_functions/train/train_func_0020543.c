xpr_has_nonsys_fcall(struct expr_t *ndp)
{
 int32 anum;
 struct sy_t *syp;
 struct sysfunc_t *syfp;

 if (ndp->optyp == FCALL)
  {
   syp = ndp->lu.x->lu.sy;
   if (syp->sytyp != SYM_SF) return(TRUE);

   syfp = syp->el.esyftbp;
   if (syfp->tftyp != SYSF_BUILTIN) return(TRUE);
   anum = __cnt_tfargs(ndp->ru.x);


   switch (syfp->syfnum) {
    case STN_ITOR: case STN_BITSTOREAL: case STN_RTOI: case STN_REALTOBITS:
    case STN_SIGNED: case STN_UNSIGNED:
    case STN_COS: case STN_SIN: case STN_TAN: case STN_ACOS: case STN_ASIN:
    case STN_ATAN: case STN_COSH: case STN_SINH: case STN_TANH:
    case STN_ATANH: case STN_ACOSH: case STN_ASINH:
    case STN_INT: case STN_SGN:
    case STN_LN: case STN_LOG10: case STN_ABS: case STN_SQRT: case STN_EXP:
    case STN_HSQRT: case STN_HLOG: case STN_HLOG10:
     if (anum != 1) { sf_errifn(syp, 1); return(TRUE); }
     break;

    case STN_POW: case STN_MIN: case STN_MAX:

    case STN_HPOW: case STN_HPWR: case STN_HSIGN: case STN_HDB:
    case STN_HYPOT: case STN_ATAN2:
     if (anum != 2) { sf_errifn(syp, 2); return(TRUE); }
     break;
    default:

     return(TRUE);
   }

  }
 if (__isleaf(ndp)) return(FALSE);

 if (ndp->lu.x != NULL) { if (xpr_has_nonsys_fcall(ndp->lu.x)) return(TRUE); }
 if (ndp->ru.x != NULL) { if (xpr_has_nonsys_fcall(ndp->ru.x)) return(TRUE); }
 return(FALSE);
}
