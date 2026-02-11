ira_compress_allocno_live_ranges (void)
{
  remove_some_program_points_and_update_live_ranges ();
  ira_rebuild_start_finish_chains ();
  if (internal_flag_ira_verbose > 2 && ira_dump_file != NULL)
    {
      fprintf (ira_dump_file, "Ranges after the compression:\n");
      print_live_ranges (ira_dump_file);
    }
}
