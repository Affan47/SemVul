x_server_local_set_vt (XServerLocal *server, gint vt)
{
    g_return_if_fail (server != NULL);
    if (server->priv->have_vt_ref)
        vt_unref (server->priv->vt);
    server->priv->have_vt_ref = FALSE;
    server->priv->vt = vt;
    if (vt > 0)
    {
        vt_ref (vt);
        server->priv->have_vt_ref = TRUE;
    }
}
