gcse_after_reload_main (rtx f ATTRIBUTE_UNUSED)
{

  memset (&stats, 0, sizeof (stats));


  alloc_mem ();


  init_alias_analysis ();

  compute_hash_table ();

  if (dump_file)
    dump_hash_table (dump_file);

  if (htab_elements (expr_table) > 0)
    {
      eliminate_partially_redundant_loads ();
      delete_redundant_insns ();

      if (dump_file)
	{
	  fprintf (dump_file, "GCSE AFTER RELOAD stats:\n");
	  fprintf (dump_file, "copies inserted: %d\n", stats.copies_inserted);
	  fprintf (dump_file, "moves inserted:  %d\n", stats.moves_inserted);
	  fprintf (dump_file, "insns deleted:   %d\n", stats.insns_deleted);
	  fprintf (dump_file, "\n\n");
	}
    }


  end_alias_analysis ();

  free_mem ();
}
