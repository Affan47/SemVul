glade_property_klass_init (GladePropertyKlass * prop_class)
{
  GObjectClass *object_class;
  g_return_if_fail (prop_class != NULL);

  parent_class = g_type_class_peek_parent (prop_class);
  object_class = G_OBJECT_CLASS (prop_class);


  object_class->set_property = glade_property_set_real_property;
  object_class->get_property = glade_property_get_real_property;
  object_class->finalize = glade_property_finalize;


  prop_class->dup = glade_property_dup_impl;
  prop_class->equals_value = glade_property_equals_value_impl;
  prop_class->set_value = glade_property_set_value_impl;
  prop_class->get_value = glade_property_get_value_impl;
  prop_class->sync = glade_property_sync_impl;
  prop_class->load = glade_property_load_impl;
  prop_class->value_changed = NULL;
  prop_class->tooltip_changed = NULL;


  properties[PROP_CLASS] =
    g_param_spec_pointer ("class",
                          _("Class"),
                          _("The GladePropertyClass for this property"),
                          G_PARAM_CONSTRUCT_ONLY | G_PARAM_READWRITE);

  properties[PROP_ENABLED] =
    g_param_spec_boolean ("enabled",
                          _("Enabled"),
                          _("If the property is optional, this is its enabled state"),
                          TRUE, G_PARAM_READWRITE);

  properties[PROP_SENSITIVE] =
    g_param_spec_boolean ("sensitive",
                          _("Sensitive"),
                          _("This gives backends control to set property sensitivity"),
                          TRUE, G_PARAM_READWRITE);

  properties[PROP_I18N_CONTEXT] =
    g_param_spec_string ("i18n-context",
                         _("Context"),
                         _("Context for translation"),
                         NULL,
                         G_PARAM_READWRITE);

  properties[PROP_I18N_COMMENT] =
    g_param_spec_string ("i18n-comment",
                         _("Comment"),
                         _("Comment for translators"),
                         NULL,
                         G_PARAM_READWRITE);

  properties[PROP_I18N_TRANSLATABLE] =
    g_param_spec_boolean ("i18n-translatable",
                          _("Translatable"),
                          _("Whether this property is translatable"),
                          TRUE,
                          G_PARAM_READWRITE);

  properties[PROP_STATE] =
    g_param_spec_int ("state",
                      _("Visual State"),
                      _("Priority information for the property editor to act on"),
                      GLADE_STATE_NORMAL,
                      G_MAXINT,
                      GLADE_STATE_NORMAL,
                      G_PARAM_READABLE);


  g_object_class_install_properties (object_class, N_PROPERTIES, properties);


  glade_property_signals[VALUE_CHANGED] =
      g_signal_new ("value-changed",
                    G_TYPE_FROM_CLASS (object_class),
                    G_SIGNAL_RUN_LAST,
                    G_STRUCT_OFFSET (GladePropertyKlass,
                                     value_changed),
                    NULL, NULL,
                    _glade_marshal_VOID__POINTER_POINTER,
                    G_TYPE_NONE, 2, G_TYPE_POINTER, G_TYPE_POINTER);

  glade_property_signals[TOOLTIP_CHANGED] =
      g_signal_new ("tooltip-changed",
                    G_TYPE_FROM_CLASS (object_class),
                    G_SIGNAL_RUN_LAST,
                    G_STRUCT_OFFSET (GladePropertyKlass,
                                     tooltip_changed),
                    NULL, NULL,
                    _glade_marshal_VOID__STRING_STRING_STRING,
                    G_TYPE_NONE, 3, G_TYPE_STRING, G_TYPE_STRING,
                    G_TYPE_STRING);

  g_type_class_add_private (prop_class, sizeof (GladePropertyPrivate));
}
