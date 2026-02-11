printWMalloc () {
  WMSTRUCT *prev = NULL;
  WMSTRUCT *curr = NULL;
  unsigned int i = 0;

  fprintf (stderr, "\tMemory used at exit:  %u\n", inuse_malloc);
  fprintf (stderr, "\tMaximum memory used at once:  %u\n", max_malloc);
  fprintf (stderr, "\tMaximum memory (MB):  %.1f\n", (double) max_malloc / (double) (1024 * 1024));

  for (i = 0; i < WM_SIZE; i++) {
    prev = NULL;
    curr = wm_array[i];

    while (curr != NULL) {
      prev = curr;
      curr = curr -> next;
      free (prev -> file);
      free (prev);
    }
  }

  free (tempstr);
  free (wm_array);

  return;
}
