list_clsf_storage ( clsf_DS clsf, search_DS search, int print_p,
                        int list_global_clsf_p)
{
  void **clsf_list_ptr = NULL;
  int num_clsf_ptrs = 0, n_try, n_model;
  int n_global_clsfs = 0;
  clsf_DS stored_clsf, global_clsf;

  if (clsf == NULL) {
    fprintf(stderr, "\n NULL clsf passed to list_clsf_storage\n");
    abort();
  }
  if (print_p == TRUE)
    printf("clsf: %p\n", (void *) clsf);
  num_clsf_ptrs++;
  clsf_list_ptr = (void **) malloc( num_clsf_ptrs * sizeof( void *));
  clsf_list_ptr[num_clsf_ptrs - 1] = (void *) clsf;

  if (list_global_clsf_p == TRUE) {
    for (n_model=0; n_model<clsf->num_models; n_model++) {
      if ((global_clsf = clsf->models[n_model]->global_clsf) != NULL) {
        if (print_p == TRUE)
          printf("model global clsf: %p\n", (void *) global_clsf);
        num_clsf_ptrs++;
        clsf_list_ptr = (void **) realloc( clsf_list_ptr, num_clsf_ptrs * sizeof( void *));
        clsf_list_ptr[num_clsf_ptrs - 1] = (void *) global_clsf;
      }
    }
  }
  if (search != NULL) {
    for (n_try=0; n_try<search->n_tries; n_try++) {
      if (search->tries[n_try]->clsf != NULL) {
        if (print_p == TRUE)
          printf("search_try_clsf %d: %p\n", n_try + 1, (void *) search->tries[n_try]->clsf);
        num_clsf_ptrs++;
        clsf_list_ptr = (void **) realloc( clsf_list_ptr, num_clsf_ptrs * sizeof( void *));
        clsf_list_ptr[num_clsf_ptrs - 1] = (void *) search->tries[n_try]->clsf;
      }
    }
  }
  if (G_clsf_store != NULL) {
    n_global_clsfs++;
    if (print_p == TRUE)
      printf("G_clsf_store %d: %p\n", n_global_clsfs, (void *) G_clsf_store);
    num_clsf_ptrs++;
    clsf_list_ptr = (void **) realloc( clsf_list_ptr, num_clsf_ptrs * sizeof( void *));
    clsf_list_ptr[num_clsf_ptrs - 1] = (void *) G_clsf_store;
    stored_clsf = G_clsf_store->next;
    while (stored_clsf != NULL) {
      n_global_clsfs++;
      if (print_p == TRUE)
        printf("G_clsf_store %d: %p\n", n_global_clsfs, (void *) stored_clsf);
      num_clsf_ptrs++;
      clsf_list_ptr = (void **) realloc( clsf_list_ptr, num_clsf_ptrs * sizeof( void *));
      clsf_list_ptr[num_clsf_ptrs - 1] = (void *) stored_clsf;
      stored_clsf = stored_clsf->next;
    }
  }
  num_clsf_ptrs++;
  clsf_list_ptr = (void **) realloc( clsf_list_ptr, num_clsf_ptrs * sizeof( void *));
  clsf_list_ptr[num_clsf_ptrs - 1] = NULL;
  return( clsf_list_ptr);
}
