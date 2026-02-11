wants_initial_setup (GdmSimpleSlave *slave)
{
        gboolean enabled = FALSE;


        if (slave->priv->have_existing_user_accounts) {
                return FALSE;
        }


        if (!can_create_environment ("gnome-initial-setup")) {
                return FALSE;
        }

        if (!gdm_settings_direct_get_boolean (GDM_KEY_INITIAL_SETUP_ENABLE, &enabled)) {
                return FALSE;
        }

        return enabled;
}
