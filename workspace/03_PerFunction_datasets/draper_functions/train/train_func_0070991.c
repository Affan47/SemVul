add_to_mem_set_list (struct propagate_block_info *pbi, rtx mem)
{
  rtx i;


  if (GET_MODE (mem) == BLKmode)
    return;

  for (i = pbi->mem_set_list; i ; i = XEXP (i, 1))
    {
      rtx e = XEXP (i, 0);
      if (rtx_equal_p (XEXP (mem, 0), XEXP (e, 0)))
	{
	  if (GET_MODE_SIZE (GET_MODE (mem)) > GET_MODE_SIZE (GET_MODE (e)))
	    {
#ifdef AUTO_INC_DEC


	      if (pbi->flags & PROP_AUTOINC)
	        PUT_MODE (e, GET_MODE (mem));
	      else
#endif
	        XEXP (i, 0) = mem;
	    }
	  return;
	}
    }

  if (pbi->mem_set_list_len < MAX_MEM_SET_LIST_LEN)
    {
#ifdef AUTO_INC_DEC


      if (pbi->flags & PROP_AUTOINC)
	mem = shallow_copy_rtx (mem);
#endif
      pbi->mem_set_list = alloc_EXPR_LIST (0, mem, pbi->mem_set_list);
      pbi->mem_set_list_len++;
    }
}
