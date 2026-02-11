cselib_invalidate_mem (rtx mem_rtx)
{
  cselib_val **vp, *v, *next;
  int num_mems = 0;
  rtx mem_addr;

  mem_addr = canon_rtx (get_addr (XEXP (mem_rtx, 0)));
  mem_rtx = canon_rtx (mem_rtx);

  vp = &first_containing_mem;
  for (v = *vp; v != &dummy_val; v = next)
    {
      bool has_mem = false;
      struct elt_loc_list **p = &v->locs;
      bool had_locs = v->locs != NULL;
      rtx setting_insn = v->locs ? v->locs->setting_insn : NULL;

      while (*p)
	{
	  rtx x = (*p)->loc;
	  cselib_val *addr;
	  struct elt_list **mem_chain;


	  if (!MEM_P (x))
	    {
	      p = &(*p)->next;
	      continue;
	    }
	  if (num_mems < PARAM_VALUE (PARAM_MAX_CSELIB_MEMORY_LOCATIONS)
	      && ! canon_true_dependence (mem_rtx, GET_MODE (mem_rtx), mem_addr,
		      			  x, NULL_RTX, cselib_rtx_varies_p))
	    {
	      has_mem = true;
	      num_mems++;
	      p = &(*p)->next;
	      continue;
	    }


	  addr = cselib_lookup (XEXP (x, 0), VOIDmode, 0, GET_MODE (x));
	  mem_chain = &addr->addr_list;
	  for (;;)
	    {
	      if ((*mem_chain)->elt == v)
		{
		  unchain_one_elt_list (mem_chain);
		  break;
		}

	      mem_chain = &(*mem_chain)->next;
	    }

	  unchain_one_elt_loc_list (p);
	}

      if (had_locs && v->locs == 0 && !PRESERVED_VALUE_P (v->val_rtx))
	{
	  if (setting_insn && DEBUG_INSN_P (setting_insn))
	    n_useless_debug_values++;
	  else
	    n_useless_values++;
	}

      next = v->next_containing_mem;
      if (has_mem)
	{
	  *vp = v;
	  vp = &(*vp)->next_containing_mem;
	}
      else
	v->next_containing_mem = NULL;
    }
  *vp = &dummy_val;
}
