presentity_view_set_property (GObject* obj,
			      guint prop_id,
			      const GValue* value,
			      GParamSpec* spec)
{
  PresentityView* self = NULL;
  Ekiga::Presentity* presentity = NULL;

  self = (PresentityView* )obj;

  switch (prop_id) {

  case PRESENTITY_VIEW_PROP_PRESENTITY:
    presentity = (Ekiga::Presentity*)g_value_get_pointer (value);
    presentity_view_set_presentity (self, presentity);

    break;

  default:
    G_OBJECT_WARN_INVALID_PROPERTY_ID (obj, prop_id, spec);
    break;
  }
}
