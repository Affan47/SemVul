parse_unopterm(void)
{
 int32 sav_xndi;
 struct expr_t *ndp, *ndp2, *unopndp, *lastndp;

 lastndp = NULL;
 unopndp = NULL;
 ndp = __exprtab[__xndi];
 switch ((byte) ndp->optyp) {

  case ID: case NUMBER: case REALNUM: return(parse_term());
  case LPAR:
do_parens:
   sav_xndi = __xndi++;
   if ((ndp2 = parse_qcexpr()) == NULL) return(NULL);
   ndp = __exprtab[__xndi];


   if (ndp->optyp == COLON)
    {
     struct expr_t *minxndp, *nomxndp;

     minxndp = ndp2;
     __xndi++;
     if ((ndp2 = parse_qcexpr()) == NULL)
      {
mintyp_err:
       if (__pv_err_cnt <= __saverr_cnt)
        __pv_ferr(1113, "mintypmax expression error at token [%s]",
         to_xndnam(__xs, __xndi));

       skip_3valend();
       return(NULL);
      }
     nomxndp = ndp2;
     ndp = __exprtab[__xndi];
     if (ndp->optyp != COLON) goto mintyp_err;
     __xndi++;
     if ((ndp2 = parse_qcexpr()) == NULL) goto mintyp_err;
     ndp = __exprtab[__xndi];
     if (ndp->optyp != RPAR) goto mintyp_err;
     if (__mintypmax_sel == DEL_MIN) ndp2 = minxndp;
     else if (__mintypmax_sel == DEL_TYP) ndp2 = nomxndp;
     __xndi++;
     if (sav_xndi == 0) __has_top_mtm = TRUE;
     goto unop_ret;
    }

   if (ndp->optyp != RPAR)
    {
     __pv_ferr(1113,
      "expression primary or mintypmax expression ending ) expected - %s read",
      to_xndnam(__xs, __xndi));
     return(NULL);
    }
   __xndi++;
   goto unop_ret;
 }
 if (is_unop(ndp->optyp))
  {
rep_unops:
   if (ndp->optyp != PLUS)
    {
     ndp = alloc_xtnd(__xndi);
     ndp->ru.x = NULL;
     if (lastndp == NULL) unopndp = ndp; else lastndp->lu.x = ndp;
     lastndp = ndp;
    }

   ndp2 = __exprtab[++__xndi];
   if (ndp2->optyp == LPAR) goto do_parens;

   if (is_unop(ndp2->optyp))
    {
     ndp = ndp2;
     goto rep_unops;
    }

   if ((ndp2 = parse_term()) == NULL) return(NULL);

unop_ret:
   if (lastndp == NULL) unopndp = ndp2; else lastndp->lu.x = ndp2;
   return(unopndp);
  }
 return(parse_term());
}
