on_handle_get_application_accept_data (UnityWebappsGenContext *context,
                                       GDBusMethodInvocation *invocation,
                                       gpointer user_data)
{
  UnityWebappsContextDaemon *daemon = (UnityWebappsContextDaemon *)user_data;
  gchar **mimes = daemon->dnd_mimes;
  GVariantBuilder *builder;
  GVariant *value;
  gchar **it;

  builder = g_variant_builder_new (G_VARIANT_TYPE ("as"));
  if (mimes)
    for (it = mimes; *it; it++)
      {
        g_variant_builder_add (builder, "s", *it);
      }
  value = g_variant_new ("(as)", builder);

  g_dbus_method_invocation_return_value (invocation,
                                         value);

  g_variant_builder_unref (builder);

  return TRUE;
}
