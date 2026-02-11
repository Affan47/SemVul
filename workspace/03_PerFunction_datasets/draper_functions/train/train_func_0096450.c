val_bind (dataflow_set *set, rtx val, rtx loc, bool modified)
{
  if (REG_P (loc))
    {
      if (modified)
	var_regno_delete (set, REGNO (loc));
      var_reg_decl_set (set, loc, VAR_INIT_STATUS_INITIALIZED,
			dv_from_value (val), 0, NULL_RTX, INSERT);
    }
  else if (MEM_P (loc))
    {
      struct elt_loc_list *l = CSELIB_VAL_PTR (val)->locs;

      if (modified)
	clobber_overlapping_mems (set, loc);

      if (l && GET_CODE (l->loc) == VALUE)
	l = canonical_cselib_val (CSELIB_VAL_PTR (l->loc))->locs;


      while (l)
	if (GET_CODE (l->loc) == MEM && XEXP (l->loc, 0) == XEXP (loc, 0))
	  break;
	else
	  l = l->next;

      if (!l)
	var_mem_decl_set (set, loc, VAR_INIT_STATUS_INITIALIZED,
			  dv_from_value (val), 0, NULL_RTX, INSERT);
    }
  else
    {


      gcc_unreachable ();
      set_variable_part (set, loc, dv_from_value (val), 0,
			 VAR_INIT_STATUS_INITIALIZED, NULL_RTX, INSERT);
    }
}
