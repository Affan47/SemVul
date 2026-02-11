cc_credentials_panel_set_property (GObject *object,
                                   guint property_id,
                                   const GValue *value,
                                   GParamSpec *pspec)
{
    CcCredentialsPanel *self = CC_CREDENTIALS_PANEL (object);
    CcCredentialsPanelPrivate *priv = self->priv;

    switch (property_id)
    {
    case PROP_ARGV:
    {
        gchar **argv;

        priv->startup_action = CREDENTIALS_ACTION_DEFAULT;

        argv = g_value_get_boxed (value);

        if (argv && argv[0])
        {
            static const gchar ACCOUNT_DETAILS[] = "account-details=";
            static const gchar APPLICATION[] = "application=";

            g_debug ("Startup argument given: %s", argv[0]);

            if (g_str_has_prefix (argv[0], ACCOUNT_DETAILS))
            {
                priv->startup_action = CREDENTIALS_ACTION_ACCOUNT_DETAILS;

                priv->account_id = atoi (argv[0]
                                         + sizeof (ACCOUNT_DETAILS)
                                         - 1);
            }
            else if (g_str_has_prefix (argv[0], APPLICATION))
            {


                priv->startup_action = CREDENTIALS_ACTION_APPLICATION;

                priv->application_name = g_strdup (argv[0]
                                                   + sizeof (APPLICATION)
                                                   - 1);
            }
        }
    }
        break;
    default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
    }
}
