glade_app_set_accel_group (GtkAccelGroup *accel_group)
{
  GladeApp *app;
  g_return_if_fail (GTK_IS_ACCEL_GROUP (accel_group));

  app = glade_app_get ();

  app->priv->accel_group = accel_group;
}
