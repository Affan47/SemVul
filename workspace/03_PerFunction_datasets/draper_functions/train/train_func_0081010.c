gnl_object_ghost_pad (GnlObject * object, const gchar * name, GstPad * target)
{
  GstPadDirection dir = GST_PAD_DIRECTION (target);
  GstPad *ghost;

  GST_DEBUG_OBJECT (object, "name:%s, target:%p", name, target);

  g_return_val_if_fail (target, FALSE);
  g_return_val_if_fail ((dir != GST_PAD_UNKNOWN), FALSE);

  ghost = gnl_object_ghost_pad_no_target (object, name, dir);
  if (!ghost) {
    GST_WARNING_OBJECT (object, "Couldn't create ghostpad");
    return NULL;
  }

  if (!(gnl_object_ghost_pad_set_target (object, ghost, target))) {
    GST_WARNING_OBJECT (object,
        "Couldn't set the target pad... removing ghostpad");
    gst_object_unref (ghost);
    return NULL;
  }

  GST_DEBUG_OBJECT (object, "activating ghostpad");

  gst_pad_set_active (ghost, TRUE);

  if (!(gst_element_add_pad (GST_ELEMENT (object), ghost))) {
    GST_WARNING ("couldn't add newly created ghostpad");
    return NULL;
  }

  return ghost;
}
