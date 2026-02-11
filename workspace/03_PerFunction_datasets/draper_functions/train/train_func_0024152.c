gdm_session_setup_for_user (GdmSession *self,
                            const char *service_name,
                            const char *username)
{

        g_return_if_fail (GDM_IS_SESSION (self));
        g_return_if_fail (username != NULL);

        gdm_session_select_user (self, username);

        send_setup_for_user (self, service_name);
        gdm_session_defaults_changed (self);
}
