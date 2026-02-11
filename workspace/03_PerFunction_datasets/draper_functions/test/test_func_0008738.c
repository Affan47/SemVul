verify_local_live_at_start (regset new_live_at_start, basic_block bb)
{
  if (reload_completed)
    {


      if (! REG_SET_EQUAL_P (new_live_at_start, bb->global_live_at_start))
	{
	  if (rtl_dump_file)
	    {
	      fprintf (rtl_dump_file,
		       "live_at_start mismatch in bb %d, aborting\nNew:\n",
		       bb->index);
	      debug_bitmap_file (rtl_dump_file, new_live_at_start);
	      fputs ("Old:\n", rtl_dump_file);
	      dump_bb (bb, rtl_dump_file);
	    }
	  abort ();
	}
    }
  else
    {
      int i;


      XOR_REG_SET (new_live_at_start, bb->global_live_at_start);

      EXECUTE_IF_SET_IN_REG_SET (new_live_at_start, 0, i,
	{

	  if (REGNO_REG_SET_P (bb->global_live_at_start, i))
	    {
	      if (rtl_dump_file)
		{
		  fprintf (rtl_dump_file,
			   "Register %d died unexpectedly.\n", i);
		  dump_bb (bb, rtl_dump_file);
		}
	      abort ();
	    }


	  verify_wide_reg (i, bb);
	});
    }
}
