dbds_continue_enumeration_p (const_basic_block bb, const void *stop)
{
  return (bb != (const_basic_block) stop
	  && bb != dbds_ce_stop);
}
