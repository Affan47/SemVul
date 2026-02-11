add_xt_block_frags (segT sec,
		    xtensa_block_info **xt_block,
		    frag_predicate property_function,
		    frag_predicate end_property_function)
{
  fragS *fragP;


  while (*xt_block != NULL)
    xt_block = &(*xt_block)->next;


  if (seg_info (sec)->frchainP)
    {
      for (fragP = seg_info (sec)->frchainP->frch_root;
	   fragP;
	   fragP = fragP->fr_next)
	{
	  if (property_function (fragP)
	      && (fragP->fr_type != rs_fill || fragP->fr_fix != 0))
	    {
	      if (*xt_block != NULL)
		{
		  if ((*xt_block)->offset + (*xt_block)->size
		      == fragP->fr_address)
		    (*xt_block)->size += fragP->fr_fix;
		  else
		    xt_block = &((*xt_block)->next);
		}
	      if (*xt_block == NULL)
		{
		  xtensa_block_info *new_block = (xtensa_block_info *)
		    xmalloc (sizeof (xtensa_block_info));
		  new_block->sec = sec;
		  new_block->offset = fragP->fr_address;
		  new_block->size = fragP->fr_fix;
		  new_block->next = NULL;
		  xtensa_frag_flags_init (&new_block->flags);
		  *xt_block = new_block;
		}
	      if (end_property_function
		  && end_property_function (fragP))
		{
		  xt_block = &((*xt_block)->next);
		}
	    }
	}
    }
}
