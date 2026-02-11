dse_transfer_function (int bb_index)
{
  bb_info_t bb_info = bb_table[bb_index];

  if (bb_info->kill)
    {
      if (bb_info->out)
	{

	  if (bb_info->in)
	    return bitmap_ior_and_compl (bb_info->in, bb_info->gen,
					 bb_info->out, bb_info->kill);
	  else
	    {
	      bb_info->in = BITMAP_ALLOC (NULL);
	      bitmap_ior_and_compl (bb_info->in, bb_info->gen,
				    bb_info->out, bb_info->kill);
	      return true;
	    }
	}
      else

	return false;
    }
  else
    {


      if (bb_info->in)
	return false;
      else
	{
	  bb_info->in = BITMAP_ALLOC (NULL);
	  bitmap_copy (bb_info->in, bb_info->gen);
	  return true;
	}
    }
}
