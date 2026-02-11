convert_value_to_boolean (GstDirectControlBinding * self, gdouble s,
    gpointer d_)
{
  gboolean *d = (gboolean *) d_;

  s = CLAMP (s, 0.0, 1.0);
  *d = (gboolean) (s + 0.5);
}
