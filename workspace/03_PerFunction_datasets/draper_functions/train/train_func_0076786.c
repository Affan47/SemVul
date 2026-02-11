can_duplicate_block_p (const_basic_block bb)
{
  if (!cfg_hooks->can_duplicate_block_p)
    internal_error ("%s does not support can_duplicate_block_p",
		    cfg_hooks->name);

  if (bb == EXIT_BLOCK_PTR || bb == ENTRY_BLOCK_PTR)
    return false;

  return cfg_hooks->can_duplicate_block_p (bb);
}
