tp_base_media_call_stream_finish_initial_candidates (
    TpSvcCallStreamInterfaceMedia *iface,
    DBusGMethodInvocation *context)
{
  TpBaseMediaCallStream *self = TP_BASE_MEDIA_CALL_STREAM (iface);
  TpBaseMediaCallStreamClass *klass =
      TP_BASE_MEDIA_CALL_STREAM_GET_CLASS (self);
  GError *error = NULL;

  if (klass->finish_initial_candidates != NULL)
    if (!klass->finish_initial_candidates (self, &error))
      {
        dbus_g_method_return_error (context, error);
        g_clear_error (&error);
        return;
      }

  tp_svc_call_stream_interface_media_return_from_finish_initial_candidates (
      context);
}
