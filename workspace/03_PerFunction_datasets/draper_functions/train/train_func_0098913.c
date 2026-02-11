clutter_get_script_id (GObject *gobject)
{
  g_return_val_if_fail (G_IS_OBJECT (gobject), NULL);

  if (CLUTTER_IS_SCRIPTABLE (gobject))
    return clutter_scriptable_get_id (CLUTTER_SCRIPTABLE (gobject));
  else
    return g_object_get_data (gobject, "clutter-script-id");
}
