forwarder_block_p (const_basic_block bb)
{
  if (!contains_no_active_insn_p (bb))
    return false;


  if (current_loops)
    {
      basic_block dest;
      if (bb->loop_father->header == bb)
	return false;
      dest = EDGE_SUCC (bb, 0)->dest;
      if (dest->loop_father->header == dest)
	return false;
    }

  return true;
}
