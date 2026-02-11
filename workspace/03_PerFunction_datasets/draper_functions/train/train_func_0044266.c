ekiga_dbus_component_call (EkigaDBusComponent *self,
                           const gchar *uri,
                           G_GNUC_UNUSED GError **error)
{
  boost::shared_ptr<Ekiga::CallCore> call_core = self->priv->service_core->get<Ekiga::CallCore> ("call-core");
  call_core->dial (uri);

  return TRUE;
}
