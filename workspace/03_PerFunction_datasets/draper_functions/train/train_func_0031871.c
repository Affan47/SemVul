gst_argb_control_binding_constructor (GType type, guint n_construct_params,
    GObjectConstructParam * construct_params)
{
  GstARGBControlBinding *self;

  self =
      GST_ARGB_CONTROL_BINDING (G_OBJECT_CLASS (parent_class)->constructor
      (type, n_construct_params, construct_params));

  if (GST_CONTROL_BINDING_PSPEC (self)) {
    if (!(G_PARAM_SPEC_VALUE_TYPE (GST_CONTROL_BINDING_PSPEC (self)) ==
            G_TYPE_UINT)) {
      GST_WARNING ("can't bind to paramspec type '%s'",
          G_PARAM_SPEC_TYPE_NAME (GST_CONTROL_BINDING_PSPEC (self)));
      GST_CONTROL_BINDING_PSPEC (self) = NULL;
    } else {
      g_value_init (&self->cur_value, G_TYPE_UINT);
    }
  }
  return (GObject *) self;
}
