metaserver_update_cache(const char *server_name, const char *server_ip) {
    int index;


    for (index = 0; index < cached_servers_num; index++) {
        if (strcmp(server_name, cached_servers_name[index]) == 0) {
            break;
        }
    }


    if (index != 0 || !cached_servers_num) {
        char *name;
        char *ip;
        int  copy;

        if (index == cached_servers_num) {


            name = strdup(server_name);
            ip = strdup(server_ip);
            cached_servers_num++;
            if (cached_servers_num > CACHED_SERVERS_MAX) {
                cached_servers_num--;
                free(cached_servers_name[cached_servers_num-1]);
                free(cached_servers_ip[cached_servers_num-1]);
            }
        } else {


            name = cached_servers_name[index];
            ip = cached_servers_ip[index];
        }


        for (copy = MIN(index, CACHED_SERVERS_MAX-1); copy > 0; copy--) {
            cached_servers_name[copy] = cached_servers_name[copy-1];
            cached_servers_ip[copy] = cached_servers_ip[copy-1];
        }


        cached_servers_name[0] = name;
        cached_servers_ip[0] = ip;
        metaserver_save_cache();
    }
}
