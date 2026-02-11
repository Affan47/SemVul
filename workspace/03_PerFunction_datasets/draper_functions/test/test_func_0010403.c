set_structure_widths (GstStructure * s, int min, int max)
{
  GValue list = { 0 };
  GValue val = { 0 };
  int width;

  if (min == max) {
    gst_structure_set (s, "width", G_TYPE_INT, min, NULL);
    return;
  }

  g_value_init (&list, GST_TYPE_LIST);
  g_value_init (&val, G_TYPE_INT);
  for (width = min; width <= max; width += 8) {
    g_value_set_int (&val, width);
    gst_value_list_append_value (&list, &val);
  }
  gst_structure_set_value (s, "width", &list);
  g_value_unset (&val);
  g_value_unset (&list);
}
