cb_typefound (GstElement *typefind,
                          guint       probability,
                          GstCaps    *caps,
                          gpointer    data)
{
  TypeFinder *self = (TypeFinder *) data;

  gchar *type = gst_caps_to_string (caps);
  self->typefound (type, probability);
  g_free (type);
}
