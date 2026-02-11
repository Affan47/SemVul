server_handle_enumerate_actions (Server                 *server,
                                 GVariant               *parameters,
                                 PolkitSubject          *caller,
                                 GDBusMethodInvocation  *invocation)
{
  GVariantBuilder builder;
  GError *error;
  GList *actions;
  GList *l;
  const gchar *locale;

  actions = NULL;

  g_variant_get (parameters, "(&s)", &locale);

  error = NULL;
  actions = polkit_backend_authority_enumerate_actions (server->authority,
                                                        caller,
                                                        locale,
                                                        &error);
  if (error != NULL)
    {
      g_dbus_method_invocation_return_gerror (invocation, error);
      g_error_free (error);
      goto out;
    }

  g_variant_builder_init (&builder, G_VARIANT_TYPE ("a(ssssssuuua{ss})"));
  for (l = actions; l != NULL; l = l->next)
    {
      PolkitActionDescription *ad = POLKIT_ACTION_DESCRIPTION (l->data);
      GVariant *value;
      value = polkit_action_description_to_gvariant (ad);
      g_variant_ref_sink (value);
      g_variant_builder_add_value (&builder, value);
      g_variant_unref (value);
    }
  g_dbus_method_invocation_return_value (invocation, g_variant_new ("(a(ssssssuuua{ss}))", &builder));

 out:
  g_list_foreach (actions, (GFunc) g_object_unref, NULL);
  g_list_free (actions);
}
