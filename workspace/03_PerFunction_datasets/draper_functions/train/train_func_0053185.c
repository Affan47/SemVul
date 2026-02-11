auth_stream_authenticate (client_t *client, const char *mount, mount_proxy *mountinfo)
{
    if (mountinfo && mountinfo->auth && mountinfo->auth->stream_auth)
    {
        auth_client *auth_user = auth_client_setup (mount, client);

        auth_user->process = stream_auth_callback;
        INFO1 ("request source auth for \"%s\"", mount);
        queue_auth_client (auth_user, mountinfo);
        return 1;
    }
    return 0;
}
