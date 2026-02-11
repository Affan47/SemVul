create_combo_box (gchar *selected_widget)
{
  ClutterActor *combo;
  gint i, set_index = 0;
  gchar *needle;
  GType types[] = {
   mx_grid_get_type (),
   mx_box_layout_get_type (),
   mx_table_get_type (),
   mx_stack_get_type (),
   mx_viewport_get_type (),
   mx_kinetic_scroll_view_get_type ()
  };

  combo = mx_combo_box_new ();

  needle = g_ascii_strdown (selected_widget, -1);

  for (i = 0; i < G_N_ELEMENTS (types); i++)
    {
      gchar *haystack;

      haystack = g_ascii_strdown (g_type_name (types[i]), -1);

      if (strstr (haystack, needle))
        set_index = i;

      g_free (haystack);

      mx_combo_box_append_text (MX_COMBO_BOX (combo), g_type_name (types[i]));
    }

  g_free (needle);

  g_signal_connect (combo, "notify::index", G_CALLBACK (change_widget), NULL);

  mx_combo_box_set_index (MX_COMBO_BOX (combo), set_index);

  return combo;
}
