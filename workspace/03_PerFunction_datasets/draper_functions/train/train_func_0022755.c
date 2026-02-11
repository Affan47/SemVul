gegl_expcombine_attach (GeglOperation *operation)
{
  GObjectClass  *object_class = G_OBJECT_GET_CLASS (operation);
  gchar padname[16];
  guint i;

  g_object_class_install_property (G_OBJECT_GET_CLASS (operation),
                                   PROP_INPUT,
                                   g_param_spec_object ("output",
                                                        "output",
                                                        "Output buffer",
                                                        GEGL_TYPE_BUFFER,
                                                        G_PARAM_READWRITE |
                                                        GEGL_PARAM_PAD_OUTPUT));
  gegl_operation_create_pad (operation,
                             g_object_class_find_property (object_class,
                                                           "output"));
  for (i = 0; i <= 99; ++i)
    {
      snprintf (padname, G_N_ELEMENTS (padname), "exposure_%u", i);
      g_object_class_install_property (G_OBJECT_GET_CLASS (operation),
                                       PROP_INPUT,
                                       g_param_spec_object (padname,
                                                            padname,
                                                            "Exposure input.",
                                                            GEGL_TYPE_BUFFER,
                                                            G_PARAM_READWRITE |
                                                            GEGL_PARAM_PAD_INPUT));
      gegl_operation_create_pad (operation,
                                 g_object_class_find_property (object_class,
                                                               padname));
    }
}
