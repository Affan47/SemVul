tp_group_mixin_get_handle_owners_async (TpSvcChannelInterfaceGroup *obj,
                                        const GArray *handles,
                                        DBusGMethodInvocation *context)
{
  GArray *ret;
  GError *error = NULL;

  if (tp_group_mixin_get_handle_owners ((GObject *) obj, handles,
        &ret, &error))
    {
      tp_svc_channel_interface_group_return_from_get_handle_owners (
          context, ret);
      g_array_unref (ret);
    }
  else
    {
      dbus_g_method_return_error (context, error);
      g_error_free (error);
    }
}
