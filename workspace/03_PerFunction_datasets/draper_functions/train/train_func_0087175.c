get_ipv4_config_address_as_string (NMIP4Config *ip4_config, const char *what)
{
        const GSList *list;
        struct in_addr addr;
        gchar *str = NULL;
        gchar tmp[INET_ADDRSTRLEN];
        NMIP4Address *address;


        list = nm_ip4_config_get_addresses (ip4_config);
        if (list == NULL)
                goto out;


        address = list->data;
        if (!strcmp (what, "address"))
                addr.s_addr = nm_ip4_address_get_address (address);
        else if (!strcmp (what, "gateway"))
                addr.s_addr = nm_ip4_address_get_gateway (address);
        else if (!strcmp (what, "netmask"))
                addr.s_addr = nm_utils_ip4_prefix_to_netmask (nm_ip4_address_get_prefix (address));
        else
                goto out;

        if (!inet_ntop (AF_INET, &addr, tmp, sizeof(tmp)))
                goto out;
        if (g_strcmp0 (tmp, "0.0.0.0") == 0)
                goto out;
        str = g_strdup (tmp);
out:
        return str;
}
