config_data_compatible(struct config_data *config1, struct config_data *config2)
{

    if(!!config1->ipv4_address != !!config2->ipv4_address ||
       !!config1->ipv6_address != !!config2->ipv6_address ||
       !!config1->ipv6_prefix != !!config2->ipv6_prefix ||
       !!config1->ipv4_prefix_delegation != !!config2->ipv4_prefix_delegation ||
       !!config1->ipv6_prefix_delegation != !!config2->ipv6_prefix_delegation)
        return 0;

    if(config1->ipv4_address) {
        if(!prefix_list_eq(config1->ipv4_address, config2->ipv4_address) != 0)
            return 0;
    }

    if(config1->ipv6_address) {
        if(!prefix_list_eq(config1->ipv6_address, config2->ipv6_address) != 0)
            return 0;
    }

    if(config1->ipv6_prefix) {
        if(!prefix_list_eq(config1->ipv6_prefix, config2->ipv6_prefix) != 0)
            return 0;
    }

    if(config1->ipv4_prefix_delegation) {
        if(!prefix_list_eq(config1->ipv4_prefix_delegation,
                           config2->ipv4_prefix_delegation) != 0)
            return 0;
    }

    if(config1->ipv6_prefix_delegation) {
        if(!prefix_list_eq(config1->ipv6_prefix_delegation,
                           config2->ipv6_prefix_delegation) != 0)
            return 0;
    }

    return 1;
}
