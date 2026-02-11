hydra_check_for_exit_condition() {
  int i, k = 0;

  if (hydra_brains.exit) {
    if (debug)
      printf("[DEBUG] exit was forced\n");
    return -1;
  }
  if (hydra_brains.targets <= hydra_brains.finished && hydra_brains.active < 1) {
    if (debug)
      printf("[DEBUG] all targets done and all heads finished\n");
    return 1;
  }
  if (hydra_brains.active < 1) {

    for (i = 0; i < hydra_options.max_use && k == 0; i++)
      if (hydra_heads[i]->active >= 0)
        k = 1;
    if (k == 0) {
      fprintf(stderr, "[ERROR] all children were disabled due too many connection errors\n");
      return -1;
    }
  }
  return 0;
}
