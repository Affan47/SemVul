e_dbus_calendar_skeleton_init (EDBusCalendarSkeleton *skeleton)
{
#if GLIB_VERSION_MAX_ALLOWED >= GLIB_VERSION_2_38
  skeleton->priv = e_dbus_calendar_skeleton_get_instance_private (skeleton);
#else
  skeleton->priv = G_TYPE_INSTANCE_GET_PRIVATE (skeleton, E_DBUS_TYPE_CALENDAR_SKELETON, EDBusCalendarSkeletonPrivate);
#endif

  g_mutex_init (&skeleton->priv->lock);
  skeleton->priv->context = g_main_context_ref_thread_default ();
  skeleton->priv->properties = g_new0 (GValue, 8);
  g_value_init (&skeleton->priv->properties[0], G_TYPE_BOOLEAN);
  g_value_init (&skeleton->priv->properties[1], G_TYPE_STRING);
  g_value_init (&skeleton->priv->properties[2], G_TYPE_BOOLEAN);
  g_value_init (&skeleton->priv->properties[3], G_TYPE_STRING);
  g_value_init (&skeleton->priv->properties[4], G_TYPE_STRV);
  g_value_init (&skeleton->priv->properties[5], G_TYPE_STRING);
  g_value_init (&skeleton->priv->properties[6], G_TYPE_STRING);
  g_value_init (&skeleton->priv->properties[7], G_TYPE_STRING);
}
