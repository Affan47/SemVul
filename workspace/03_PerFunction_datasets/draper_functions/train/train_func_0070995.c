GC_print_static_roots(void)
  {
    int i;
    size_t total = 0;

    for (i = 0; i < n_root_sets; i++) {
        GC_printf("From %p to %p%s\n",
                  GC_static_roots[i].r_start,
                  GC_static_roots[i].r_end,
                  GC_static_roots[i].r_tmp ? " (temporary)" : "");
        total += GC_static_roots[i].r_end - GC_static_roots[i].r_start;
    }
    GC_printf("Total size: %ld\n", (unsigned long) total);
    if (GC_root_size != total) {
        GC_err_printf("GC_root_size incorrect: %ld!!\n",
                      (long) GC_root_size);
    }
  }
