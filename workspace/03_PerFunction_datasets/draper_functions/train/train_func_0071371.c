peer_is_client (SyncevoConfig *config)
{
    char *is_client;

    g_return_val_if_fail (config, FALSE);

    syncevo_config_get_value (config, NULL, "PeerIsClient", &is_client);
    return is_client && g_strcmp0 ("1", is_client) == 0;
}
