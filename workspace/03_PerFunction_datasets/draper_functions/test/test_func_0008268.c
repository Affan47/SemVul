preserve_only_constants (void **x, void *info ATTRIBUTE_UNUSED)
{
  cselib_val *v = (cselib_val *)*x;

  if (v->locs != NULL
      && v->locs->next == NULL)
    {
      if (CONSTANT_P (v->locs->loc)
	  && (GET_CODE (v->locs->loc) != CONST
	      || !references_value_p (v->locs->loc, 0)))
	return 1;
      if (cfa_base_preserved_val)
	{
	  if (v == cfa_base_preserved_val)
	    return 1;
	  if (GET_CODE (v->locs->loc) == PLUS
	      && CONST_INT_P (XEXP (v->locs->loc, 1))
	      && XEXP (v->locs->loc, 0) == cfa_base_preserved_val->val_rtx)
	    return 1;
	}
    }

  htab_clear_slot (cselib_hash_table, x);
  return 1;
}
