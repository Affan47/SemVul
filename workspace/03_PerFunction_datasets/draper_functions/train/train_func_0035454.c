merge_equiv_classes (struct table_elt *class1, struct table_elt *class2)
{
  struct table_elt *elt, *next, *new_elt;


  class1 = class1->first_same_value;
  class2 = class2->first_same_value;


  if (class1 == class2)
    return;

  for (elt = class2; elt; elt = next)
    {
      unsigned int hash;
      rtx exp = elt->exp;
      enum machine_mode mode = elt->mode;

      next = elt->next_same_value;


      if (REG_P (exp) || exp_equiv_p (exp, exp, 1, false))
	{
	  bool need_rehash = false;

	  hash_arg_in_memory = 0;
	  hash = HASH (exp, mode);

	  if (REG_P (exp))
	    {
	      need_rehash = REGNO_QTY_VALID_P (REGNO (exp));
	      delete_reg_equiv (REGNO (exp));
	    }

	  if (REG_P (exp) && REGNO (exp) >= FIRST_PSEUDO_REGISTER)
	    remove_pseudo_from_table (exp, hash);
	  else
	    remove_from_table (elt, hash);

	  if (insert_regs (exp, class1, 0) || need_rehash)
	    {
	      rehash_using_reg (exp);
	      hash = HASH (exp, mode);
	    }
	  new_elt = insert (exp, class1, hash, mode);
	  new_elt->in_memory = hash_arg_in_memory;
	}
    }
}
