write_dependence_p (const_rtx mem,
		    	           const_rtx x, enum machine_mode x_mode, rtx x_addr,
				   	         bool mem_canonicalized, bool x_canonicalized, bool writep)
{
  rtx mem_addr;
  rtx base;
  int ret;

  gcc_checking_assert (x_canonicalized
  		              ? (x_addr != NULL_RTX && x_mode != VOIDmode)
			      	       : (x_addr == NULL_RTX && x_mode == VOIDmode));

  if (MEM_VOLATILE_P (x) && MEM_VOLATILE_P (mem))
    return 1;


  if (GET_MODE (x) == BLKmode && GET_CODE (XEXP (x, 0)) == SCRATCH)
    return 1;
  if (GET_MODE (mem) == BLKmode && GET_CODE (XEXP (mem, 0)) == SCRATCH)
    return 1;
  if (MEM_ALIAS_SET (x) == ALIAS_SET_MEMORY_BARRIER
      || MEM_ALIAS_SET (mem) == ALIAS_SET_MEMORY_BARRIER)
    return 1;


  if (!writep && MEM_READONLY_P (mem))
    return 0;


  if (MEM_ADDR_SPACE (mem) != MEM_ADDR_SPACE (x))
    return 1;

  mem_addr = XEXP (mem, 0);
  if (!x_addr)
    {
      x_addr = XEXP (x, 0);
      if (!((GET_CODE (x_addr) == VALUE
	     && GET_CODE (mem_addr) != VALUE
	     && reg_mentioned_p (x_addr, mem_addr))
	    || (GET_CODE (x_addr) != VALUE
		&& GET_CODE (mem_addr) == VALUE
		&& reg_mentioned_p (mem_addr, x_addr))))
	{
	  x_addr = get_addr (x_addr);
	  if (!mem_canonicalized)
	    mem_addr = get_addr (mem_addr);
	}
    }

  if (! writep)
    {
      base = find_base_term (mem_addr);
      if (base && (GET_CODE (base) == LABEL_REF
		   || (GET_CODE (base) == SYMBOL_REF
		       && CONSTANT_POOL_ADDRESS_P (base))))
	return 0;
    }

  if (! base_alias_check (x_addr, mem_addr, GET_MODE (x),
			  GET_MODE (mem)))
    return 0;

  if (!x_canonicalized)
    {
      x_addr = canon_rtx (x_addr);
      x_mode = GET_MODE (x);
    }
  if (!mem_canonicalized)
    mem_addr = canon_rtx (mem_addr);

  if ((ret = memrefs_conflict_p (SIZE_FOR_MODE (mem), mem_addr,
				 GET_MODE_SIZE (x_mode), x_addr, 0)) != -1)
    return ret;

  if (nonoverlapping_memrefs_p (x, mem, false))
    return 0;

  return rtx_refs_may_alias_p (x, mem, false);
}
