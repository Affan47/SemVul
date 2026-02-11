vnc_connection_gather_sasl_credentials(VncConnection *conn,
                                       sasl_interact_t *interact)
{
    VncConnectionPrivate *priv = conn->priv;
    int ninteract;

    priv->want_cred_password = FALSE;
    priv->want_cred_username = FALSE;
    priv->want_cred_x509 = FALSE;

    for (ninteract = 0 ; interact[ninteract].id != 0 ; ninteract++) {
        switch (interact[ninteract].id) {
        case SASL_CB_AUTHNAME:
        case SASL_CB_USER:
            priv->want_cred_username = TRUE;
            break;

        case SASL_CB_PASS:
            priv->want_cred_password = TRUE;
            break;

        default:
            VNC_DEBUG("Unsupported credential %lu",
                      interact[ninteract].id);

            return FALSE;
        }
    }

    if ((priv->want_cred_password ||
         priv->want_cred_username) &&
        !vnc_connection_gather_credentials(conn)) {
        VNC_DEBUG("%s", "cannot gather sasl credentials");
        return FALSE;
    }

    for (ninteract = 0 ; interact[ninteract].id != 0 ; ninteract++) {
        switch (interact[ninteract].id) {
        case SASL_CB_AUTHNAME:
        case SASL_CB_USER:
            interact[ninteract].result = priv->cred_username;
            interact[ninteract].len = strlen(priv->cred_username);
            VNC_DEBUG("Gather Username %s", priv->cred_username);
            break;

        case SASL_CB_PASS:
            interact[ninteract].result =  priv->cred_password;
            interact[ninteract].len = strlen(priv->cred_password);

            break;

        default:
            g_warn_if_reached();
        }
    }

    VNC_DEBUG("%s", "Filled SASL interact");

    return TRUE;
}
