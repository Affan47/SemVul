vnc_connection_has_credentials(gpointer data)
{
    VncConnection *conn = data;
    VncConnectionPrivate *priv = conn->priv;

    if (priv->has_error)
        return TRUE;
    if (priv->want_cred_username && !priv->cred_username)
        return FALSE;
    if (priv->want_cred_password && !priv->cred_password)
        return FALSE;


    if (priv->want_cred_x509 && !priv->cred_x509_cacert)
        return FALSE;
    return TRUE;
}
