__alloc_exprnd(void)
{
 struct expr_t *ndp;


 if (++__last_xtk >= __exprtabsiz - 1) grow_exprtab();
 if ((ndp = __exprtab[__last_xtk]) == NULL)
  {
   ndp = my_xndalloc();
   __exprtab[__last_xtk] = ndp;
  }
 __init_xnd(ndp);
 return(ndp);
}
