cse_prescan_path (struct cse_basic_block_data *data)
{
  int nsets = 0;
  int path_size = data->path_size;
  int path_entry;


  for (path_entry = 0; path_entry < path_size; path_entry++)
    {
      basic_block bb;
      rtx insn;

      bb = data->path[path_entry].bb;

      FOR_BB_INSNS (bb, insn)
	{
	  if (!INSN_P (insn))
	    continue;


	  if (GET_CODE (PATTERN (insn)) == PARALLEL)
	    nsets += XVECLEN (PATTERN (insn), 0);
	  else
	    nsets += 1;
	}
    }

  data->nsets = nsets;
}
