put_addressof_into_stack (r, ht)
     rtx r;
     htab_t ht;
{
  tree decl, type;
  int volatile_p, used_p;

  rtx reg = XEXP (r, 0);

  if (GET_CODE (reg) != REG)
    abort ();

  decl = ADDRESSOF_DECL (r);
  if (decl)
    {
      type = TREE_TYPE (decl);
      volatile_p = (TREE_CODE (decl) != SAVE_EXPR
		    && TREE_THIS_VOLATILE (decl));
      used_p = (TREE_USED (decl)
		|| (DECL_P (decl) && DECL_INITIAL (decl) != 0));
    }
  else
    {
      type = NULL_TREE;
      volatile_p = 0;
      used_p = 1;
    }

  put_reg_into_stack (0, reg, type, GET_MODE (reg), ADDRESSOF_REGNO (r),
		      volatile_p, used_p, 0, ht);
}
