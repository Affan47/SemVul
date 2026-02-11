_clutter_paint_node_create (GType gtype)
{
  g_return_val_if_fail (g_type_is_a (gtype, CLUTTER_TYPE_PAINT_NODE), NULL);

  _clutter_paint_node_init_types ();

  return (gpointer) g_type_create_instance (gtype);
}
