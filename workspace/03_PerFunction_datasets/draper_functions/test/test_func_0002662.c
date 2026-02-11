gsp_app_reload_at (GspApp       *app,
                   const char   *path,
                   unsigned int  xdg_position)
{
        g_return_if_fail (GSP_IS_APP (app));

        app->priv->xdg_position = G_MAXUINT;
        gsp_app_new (path, xdg_position);
}
