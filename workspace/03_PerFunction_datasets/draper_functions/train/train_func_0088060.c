vnc_connection_perform_auth(VncConnection *conn)
{
    VncConnectionPrivate *priv = conn->priv;
    unsigned int nauth, i;
    unsigned int auth[10];

    if (priv->minor <= 6) {
        nauth = 1;
        auth[0] = vnc_connection_read_u32(conn);
    } else {
        nauth = vnc_connection_read_u8(conn);
        if (vnc_connection_has_error(conn))
            return FALSE;

        if (nauth == 0)
            return vnc_connection_check_auth_result(conn);

        if (nauth > sizeof(auth)) {
            priv->has_error = TRUE;
            return FALSE;
        }
        for (i = 0 ; i < nauth ; i++)
            auth[i] = vnc_connection_read_u8(conn);
    }

    for (i = 0 ; i < nauth ; i++) {
        VNC_DEBUG("Possible auth %u", auth[i]);
    }

    if (priv->has_error)
        return FALSE;
    vnc_connection_choose_auth(conn, VNC_AUTH_CHOOSE_TYPE, nauth, auth);
    if (priv->has_error)
        return FALSE;

    VNC_DEBUG("Waiting for auth type");
    g_condition_wait(vnc_connection_has_auth_type, conn);
    if (priv->has_error)
        return FALSE;

    VNC_DEBUG("Choose auth %u", priv->auth_type);
    if (!vnc_connection_gather_credentials(conn))
        return FALSE;

    if (priv->minor > 6) {
        vnc_connection_write_u8(conn, priv->auth_type);
        vnc_connection_flush(conn);
    }

    switch (priv->auth_type) {
    case VNC_CONNECTION_AUTH_NONE:
        if (priv->minor == 8)
            return vnc_connection_check_auth_result(conn);
        return TRUE;
    case VNC_CONNECTION_AUTH_VNC:
        return vnc_connection_perform_auth_vnc(conn);

    case VNC_CONNECTION_AUTH_TLS:
        if (priv->minor < 7)
            return FALSE;
        return vnc_connection_perform_auth_tls(conn);

    case VNC_CONNECTION_AUTH_VENCRYPT:
        return vnc_connection_perform_auth_vencrypt(conn);

#ifdef HAVE_SASL
    case VNC_CONNECTION_AUTH_SASL:
        return vnc_connection_perform_auth_sasl(conn);
#endif

    case VNC_CONNECTION_AUTH_MSLOGON:
        return vnc_connection_perform_auth_mslogon(conn);

    case VNC_CONNECTION_AUTH_ARD:
        return vnc_connection_perform_auth_ard(conn);

    default:
        {
            struct signal_data sigdata;
            sigdata.params.authUnsupported = priv->auth_type;
            vnc_connection_emit_main_context(conn, VNC_AUTH_UNSUPPORTED, &sigdata);
            priv->has_error = TRUE;
        }
        return FALSE;
    }

    return TRUE;
}
