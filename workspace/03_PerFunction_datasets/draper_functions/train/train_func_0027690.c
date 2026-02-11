file_service (output_plugin* log,asset *main, serv_asset *service, connection *cxt)
{
    if ((FILE*)log->data != NULL) {
        uint8_t tmp_ttl;
        static char ip_addr_s[INET6_ADDRSTRLEN];
        u_ntop(main->ip_addr, main->af, ip_addr_s);

        fprintf((FILE*)log->data, "%s,%u,%d,%d,",
            ip_addr_s, main->vlan ? ntohs(main->vlan) : 0,
            ntohs(service->port),service->proto);
        if (service->role == SC_SERVER) {
            fprintf((FILE*)log->data, "SERVER,[%s:%s]",
                (char*)bdata(service->service),
                (char *)bdata(service->application));
        } else {
            fprintf((FILE*)log->data, "CLIENT,[%s:%s]",
                (char*)bdata(service->service),
                (char*)bdata(service->application));
        }

        tmp_ttl = normalize_ttl(service->ttl);
        fprintf((FILE*)log->data, ",%d,%lu\n",tmp_ttl - service->ttl,service->last_seen);
        fflush((FILE*)log->data);
    } else {
        if(log->flags & CONFIG_VERBOSE )
           elog("[!] ERROR:  File handle not open!\n");
    }
}
