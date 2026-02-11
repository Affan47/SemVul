run (gpointer data)
{
  gchar **s;

  if (keys) {
    if (introspect_elements) {
      for (s = introspect_elements; *s; s++) {
        introspect_key (*s);
      }
    } else {
        list_all_keys ();
    }
  } else {
    if (introspect_elements) {
      for (s = introspect_elements; *s; s++) {
        introspect_source (*s);
      }
    } else {
      list_all_sources ();
    }
  }

  g_main_loop_quit (mainloop);

  return FALSE;
}
