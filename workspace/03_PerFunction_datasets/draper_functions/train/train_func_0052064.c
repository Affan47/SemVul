df_grow_bb_info (struct dataflow *dflow)
{
  unsigned int new_size = last_basic_block + 1;
  if (dflow->block_info_size < new_size)
    {
      new_size += new_size / 4;
      dflow->block_info
         = (void *)XRESIZEVEC (char, (char *)dflow->block_info,
			       new_size
			       * dflow->problem->block_info_elt_size);
      memset ((char *)dflow->block_info
	      + dflow->block_info_size
	      * dflow->problem->block_info_elt_size,
	      0,
	      (new_size - dflow->block_info_size)
	      * dflow->problem->block_info_elt_size);
      dflow->block_info_size = new_size;
    }
}
