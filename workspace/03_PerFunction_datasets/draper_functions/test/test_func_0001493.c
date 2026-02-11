gdm_session_defaults_changed (GdmSession *self)
{

        if (self->priv->greeter_interface != NULL) {
                gdm_dbus_greeter_emit_default_language_name_changed (self->priv->greeter_interface,
                                                                     get_default_language_name (self));
                gdm_dbus_greeter_emit_default_session_name_changed (self->priv->greeter_interface,
                                                                    get_default_session_name (self));
        }
}
