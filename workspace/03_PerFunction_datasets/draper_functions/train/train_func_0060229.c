gst_element_populate_std_props (GObjectClass * klass, const gchar * prop_name,
    guint arg_id, GParamFlags flags)
{
  GQuark prop_id = g_quark_from_string (prop_name);
  GParamSpec *pspec;

  static GQuark fd_id = 0;
  static GQuark blocksize_id;
  static GQuark bytesperread_id;
  static GQuark dump_id;
  static GQuark filesize_id;
  static GQuark mmapsize_id;
  static GQuark location_id;
  static GQuark offset_id;
  static GQuark silent_id;
  static GQuark touch_id;

  flags |= G_PARAM_STATIC_STRINGS;

  if (!fd_id) {
    fd_id = g_quark_from_static_string ("fd");
    blocksize_id = g_quark_from_static_string ("blocksize");
    bytesperread_id = g_quark_from_static_string ("bytesperread");
    dump_id = g_quark_from_static_string ("dump");
    filesize_id = g_quark_from_static_string ("filesize");
    mmapsize_id = g_quark_from_static_string ("mmapsize");
    location_id = g_quark_from_static_string ("location");
    offset_id = g_quark_from_static_string ("offset");
    silent_id = g_quark_from_static_string ("silent");
    touch_id = g_quark_from_static_string ("touch");
  }

  if (prop_id == fd_id) {
    pspec = g_param_spec_int ("fd", "File-descriptor",
        "File-descriptor for the file being read", 0, G_MAXINT, 0, flags);
  } else if (prop_id == blocksize_id) {
    pspec = g_param_spec_ulong ("blocksize", "Block Size",
        "Block size to read per buffer", 0, G_MAXULONG, 4096, flags);

  } else if (prop_id == bytesperread_id) {
    pspec = g_param_spec_int ("bytesperread", "Bytes per read",
        "Number of bytes to read per buffer", G_MININT, G_MAXINT, 0, flags);

  } else if (prop_id == dump_id) {
    pspec = g_param_spec_boolean ("dump", "Dump",
        "Dump bytes to stdout", FALSE, flags);

  } else if (prop_id == filesize_id) {
    pspec = g_param_spec_int64 ("filesize", "File Size",
        "Size of the file being read", 0, G_MAXINT64, 0, flags);

  } else if (prop_id == mmapsize_id) {
    pspec = g_param_spec_ulong ("mmapsize", "mmap() Block Size",
        "Size in bytes of mmap()d regions", 0, G_MAXULONG, 4 * 1048576, flags);

  } else if (prop_id == location_id) {
    pspec = g_param_spec_string ("location", "File Location",
        "Location of the file to read", NULL, flags);

  } else if (prop_id == offset_id) {
    pspec = g_param_spec_int64 ("offset", "File Offset",
        "Byte offset of current read pointer", 0, G_MAXINT64, 0, flags);

  } else if (prop_id == silent_id) {
    pspec = g_param_spec_boolean ("silent", "Silent", "Don't produce events",
        FALSE, flags);

  } else if (prop_id == touch_id) {
    pspec = g_param_spec_boolean ("touch", "Touch read data",
        "Touch data to force disk read before " "push ()", TRUE, flags);
  } else {
    g_warning ("Unknown - 'standard' property '%s' id %d from klass %s",
        prop_name, arg_id, g_type_name (G_OBJECT_CLASS_TYPE (klass)));
    pspec = NULL;
  }

  if (pspec) {
    g_object_class_install_property (klass, arg_id, pspec);
  }
}
