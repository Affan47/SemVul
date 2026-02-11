GC_rebuild_root_index(void)
  {
    int i;

    for (i = 0; i < RT_SIZE; i++) GC_root_index[i] = 0;
    for (i = 0; i < n_root_sets; i++)
        add_roots_to_index(GC_static_roots + i);
  }
