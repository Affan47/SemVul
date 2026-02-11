on_shell_appeared (GDBusConnection *connection,
                   const gchar     *name,
                   const gchar     *name_owner,
                   gpointer         user_data)
{
  PluginObject *obj = (PluginObject*) user_data;

  if (obj->restart_listener)
    {
      NPVariant result = { NPVariantType_Void };

      funcs.invokeDefault (obj->instance, obj->restart_listener,
                           NULL, 0, &result);

      funcs.releasevariantvalue (&result);
    }
}
