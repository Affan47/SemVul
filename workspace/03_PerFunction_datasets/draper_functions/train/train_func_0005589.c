var_reg_delete_and_set (dataflow_set *set, rtx loc, bool modify,
			enum var_init_status initialized, rtx set_src)
{
  tree decl = REG_EXPR (loc);
  HOST_WIDE_INT offset = REG_OFFSET (loc);
  attrs node, next;
  attrs *nextp;

  decl = var_debug_decl (decl);

  if (initialized == VAR_INIT_STATUS_UNKNOWN)
    initialized = get_init_value (set, loc, dv_from_decl (decl));

  nextp = &set->regs[REGNO (loc)];
  for (node = *nextp; node; node = next)
    {
      next = node->next;
      if (dv_as_opaque (node->dv) != decl || node->offset != offset)
	{
	  delete_variable_part (set, node->loc, node->dv, node->offset);
	  pool_free (attrs_pool, node);
	  *nextp = next;
	}
      else
	{
	  node->loc = loc;
	  nextp = &node->next;
	}
    }
  if (modify)
    clobber_variable_part (set, loc, dv_from_decl (decl), offset, set_src);
  var_reg_set (set, loc, initialized, set_src);
}
