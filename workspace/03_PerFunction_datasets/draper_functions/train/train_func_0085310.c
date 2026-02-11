sra_deinitialize (void)
{
  BITMAP_FREE (candidate_bitmap);
  BITMAP_FREE (should_scalarize_away_bitmap);
  BITMAP_FREE (cannot_scalarize_away_bitmap);
  free_alloc_pool (access_pool);
  free_alloc_pool (link_pool);
  obstack_free (&name_obstack, NULL);

  pointer_map_traverse (base_access_vec, delete_base_accesses, NULL);
  pointer_map_destroy (base_access_vec);
}
