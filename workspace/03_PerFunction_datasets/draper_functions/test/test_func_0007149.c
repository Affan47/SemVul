GGobiFromWidget (GtkWidget * w, gboolean useWindow)
{
  ggobid *gg = NULL;
  GObject *obj;
  obj = g_object_get_data (G_OBJECT (w), GGobiGTKey);
  if (obj) {
    gg = (ggobid *) obj;
    ValidateGGobiRef (gg, true);
  }

  return (gg);
}
