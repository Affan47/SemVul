auth_postprocess_source (auth_client *auth_user)
{
    client_t *client = auth_user->client;
    const char *mount = auth_user->mount;
    const char *req = httpp_getvar (client->parser, HTTPP_VAR_URI);

    auth_user->client = NULL;
    client->authenticated = 1;
    if (strcmp (req, "/admin.cgi") == 0 || strncmp ("/admin/metadata", req, 15) == 0)
    {
        DEBUG2 ("metadata request (%s, %s)", req, mount);
        admin_handle_request (client, "/admin/metadata");
    }
    else
    {
        DEBUG1 ("on mountpoint %s", mount);
        source_startup (client, mount, 0);
    }
}
