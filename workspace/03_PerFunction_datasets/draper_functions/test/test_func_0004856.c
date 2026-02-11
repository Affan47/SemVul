check_all_empty_except_final (struct switch_conv_info *info)
{
  edge e;
  edge_iterator ei;

  FOR_EACH_EDGE (e, ei, info->switch_bb->succs)
    {
      if (e->dest == info->final_bb)
	continue;

      if (!empty_block_p (e->dest))
	{
	  info->reason = "bad case - a non-final BB not empty";
	  return false;
	}
    }

  return true;
}
