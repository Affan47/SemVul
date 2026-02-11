auth_remove_listener (auth_t *auth, auth_client *auth_user)
{
    client_t *client = auth_user->client;

    if (client->auth->release_listener)
        client->auth->release_listener (auth_user);
    auth_release (client->auth);
    client->auth = NULL;

    client->authenticated = 0;
}
