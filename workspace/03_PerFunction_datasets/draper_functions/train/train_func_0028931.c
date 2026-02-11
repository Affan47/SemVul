copy_config_data(struct config_data *config)
{
    struct config_data *c = malloc(sizeof(struct config_data));
    if(c == NULL)
        return NULL;

    *c = *config;

#define COPY(field) \
    do { if(c->field) c->field = copy_prefix_list(c->field); } while(0)
    COPY(server_ipv6);
    COPY(server_ipv4);
    COPY(ipv6_prefix);
    COPY(ipv4_prefix);
    COPY(ipv6_address);
    COPY(ipv4_address);
    COPY(ipv6_prefix_delegation);
    COPY(ipv4_prefix_delegation);
    COPY(name_server);
    COPY(ntp_server);
    COPY(our_ipv6_address);
#undef COPY

    return c;
}
