free_pre_mem (void)
{
  sbitmap_vector_free (transp);
  sbitmap_vector_free (comp);


  if (pre_optimal)
    sbitmap_vector_free (pre_optimal);
  if (pre_redundant)
    sbitmap_vector_free (pre_redundant);
  if (pre_insert_map)
    sbitmap_vector_free (pre_insert_map);
  if (pre_delete_map)
    sbitmap_vector_free (pre_delete_map);

  transp = comp = NULL;
  pre_optimal = pre_redundant = pre_insert_map = pre_delete_map = NULL;
}
