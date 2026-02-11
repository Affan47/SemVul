gnl_filesource_class_init (GnlFileSourceClass * klass)
{
  GObjectClass *gobject_class;
  GstElementClass *gstelement_class;

  gobject_class = (GObjectClass *) klass;
  gstelement_class = (GstElementClass *) klass;

  parent_class = g_type_class_ref (GNL_TYPE_URI_SOURCE);

  GST_DEBUG_CATEGORY_INIT (gnlfilesource, "gnlfilesource",
      GST_DEBUG_FG_BLUE | GST_DEBUG_BOLD, "GNonLin File Source Element");

  gobject_class->set_property = GST_DEBUG_FUNCPTR (gnl_filesource_set_property);
  gobject_class->get_property = GST_DEBUG_FUNCPTR (gnl_filesource_get_property);

  g_object_class_install_property (gobject_class, ARG_LOCATION,
      g_param_spec_string ("location", "Location",
          "Location of the file to use", NULL, G_PARAM_READWRITE));

  gst_element_class_add_pad_template (gstelement_class,
      gst_static_pad_template_get (&gnl_filesource_src_template));
}
