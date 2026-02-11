metaserver_save_cache(void) {
    FILE *cache;
    int server;

    if (!cached_server_file)
        return;

    cache = fopen(cached_server_file, "w");
    if (!cache)
        return;

    for (server = 0; server < cached_servers_num; server++) {
        fprintf(cache, "%s\n", cached_servers_name[server]);
        fprintf(cache, "%s\n", cached_servers_ip[server]);
    }
    fclose(cache);
}
