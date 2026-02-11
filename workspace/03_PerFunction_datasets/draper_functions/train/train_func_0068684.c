unknown_type (GstElement * element, GstPad * pad, GstCaps * caps,
    GstPlayBaseBin * play_base_bin)
{
  const gchar *type_name;
  GstStreamInfo *info;
  GstPlayBaseGroup *group;

  type_name = gst_structure_get_name (gst_caps_get_structure (caps, 0));
  if (type_name && !IS_BLACKLISTED_MIME (type_name)) {
    gchar *capsstr;

    capsstr = gst_caps_to_string (caps);
    GST_DEBUG_OBJECT (play_base_bin, "don't know how to handle %s", capsstr);

    g_message ("don't know how to handle %s", capsstr);
    g_free (capsstr);
  } else {

    GST_DEBUG_OBJECT (play_base_bin, "media type %s not handled on purpose, "
        "not posting a missing-plugin message on the bus", type_name);
  }

  GROUP_LOCK (play_base_bin);

  group = get_building_group (play_base_bin);


  info = gst_stream_info_new (GST_OBJECT_CAST (pad), GST_STREAM_TYPE_UNKNOWN,
      NULL, caps);
  info->origin = GST_OBJECT_CAST (pad);
  add_stream (group, info);

  GROUP_UNLOCK (play_base_bin);
}
