__exec_dist_poisson(struct expr_t *ndp)
{
 int32 mean, u2;
 word32 val;
 struct expr_t *fax, *a1xp, *a2xp;
 struct xstk_t *xsp, *xsp2;


 fax = ndp->ru.x;

 if (fax == NULL) __arg_terr(__FILE__, __LINE__);
 a1xp = fax->lu.x;
 if ((fax = fax->ru.x) == NULL) __arg_terr(__FILE__, __LINE__);
 a2xp = fax->lu.x;


 if (a1xp->optyp == OPEMPTY || a2xp->optyp == OPEMPTY)
  {
   __sgfwarn(588,
   "$dist_poisson arguments must not be missing (,, form) - returning 32'bx");
   goto ret_x;
  }


 xsp = __eval_xpr(a1xp);
 if (xsp->bp[0] != 0)
  {
   __sgfwarn(588,
    "$dist_poisson seed value %s has x/z bits - returning 32'bx",
    __regab_tostr(__xs, xsp->ap, xsp->bp, xsp->xslen, BHEX, FALSE));
   xsp->bp[0] = 0L;
   __pop_xstk();
ret_x:
   push_xstk_(xsp, WBITS);
   xsp->ap[0] = ALL1W;
   xsp->bp[0] = ALL1W;
   return;
  }
 __seed = (int32) xsp->ap[0];
 __pop_xstk();

 if (!__get_eval_word(a2xp, &val))
  {
   __sgfwarn(588,
    "$dist_poisson argument 2, mean value %s x/z - returning 32'bx",
    __msgexpr_tostr(__xs, a2xp));
   goto ret_x;
  }
 mean = (int32) val;


 u2 = poisson_dev(mean, &__seed);

 push_xstk_(xsp, WBITS);
 xsp->bp[0] = 0L;
 xsp->ap[0] = (word32) u2;

 push_xstk_(xsp2, WBITS);
 xsp2->ap[0] = (word32) __seed;
 xsp2->bp[0] = 0L;
 __exec2_proc_assign(a1xp, xsp2->ap, xsp2->bp);
 __pop_xstk();
}
