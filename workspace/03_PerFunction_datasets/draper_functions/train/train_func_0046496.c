delete_update_ssa (void)
{
  unsigned i;
  bitmap_iterator bi;

  sbitmap_free (old_ssa_names);
  old_ssa_names = NULL;

  sbitmap_free (new_ssa_names);
  new_ssa_names = NULL;

  BITMAP_FREE (symbols_to_rename_set);
  symbols_to_rename_set = NULL;
  symbols_to_rename.release ();

  if (names_to_release)
    {
      EXECUTE_IF_SET_IN_BITMAP (names_to_release, 0, i, bi)
	release_ssa_name (ssa_name (i));
      BITMAP_FREE (names_to_release);
    }

  clear_ssa_name_info ();

  fini_ssa_renamer ();

  if (blocks_with_phis_to_rewrite)
    EXECUTE_IF_SET_IN_BITMAP (blocks_with_phis_to_rewrite, 0, i, bi)
      {
	gimple_vec phis = phis_to_rewrite[i];
	phis.release ();
	phis_to_rewrite[i].create (0);
      }

  BITMAP_FREE (blocks_with_phis_to_rewrite);
  BITMAP_FREE (blocks_to_update);

  update_ssa_initialized_fn = NULL;
}
