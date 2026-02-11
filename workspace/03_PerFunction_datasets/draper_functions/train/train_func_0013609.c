ghost_up (GstElement * e, GstPad * pad)
{
  static gint ghost_pad_index = 0;
  GstPad *gpad;
  gchar *name;
  GstState current;
  GstState next;
  GstObject *parent = GST_OBJECT_PARENT (e);

  name = g_strdup_printf ("ghost%d", ghost_pad_index++);
  gpad = gst_ghost_pad_new (name, pad);
  g_free (name);

  GST_STATE_LOCK (e);
  gst_element_get_state (e, &current, &next, 0);

  if (current > GST_STATE_READY || next == GST_STATE_PAUSED)
    gst_pad_set_active (gpad, TRUE);

  if (!gst_element_add_pad ((GstElement *) parent, gpad)) {
    g_warning ("Pad named %s already exists in element %s\n",
        GST_OBJECT_NAME (gpad), GST_OBJECT_NAME (parent));
    gst_object_unref ((GstObject *) gpad);
    GST_STATE_UNLOCK (e);
    return NULL;
  }
  GST_STATE_UNLOCK (e);

  return gpad;
}
