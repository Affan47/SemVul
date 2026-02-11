update_fraction(gpointer p) {
  fraction_set_args_t *args = (fraction_set_args_t *) p;

  if (args != NULL) {
    gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(args->progress), args->fraction);
    g_free(args);
  }
  return FALSE;
}
