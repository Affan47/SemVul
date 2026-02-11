draw_label(gpointer p) {
  draw_label_args_t *args = (draw_label_args_t *) p;

  if (args != NULL) {
    if (args->label != NULL && args->text != NULL) {
      gtk_label_set_text(GTK_LABEL(args->label), args->text);
    }
    if (args->text != NULL)
      g_free(args->text);
    g_free(args);
  }
  return FALSE;
}
