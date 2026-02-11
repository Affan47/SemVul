add_direct_addr (struct in_addr *addr, struct in_addr *mask, int negative)
{
    struct in_addr iaddr;
    char *s;
    if ( MAX_DIRECT_ADDR_LIST <= n_direct_addr_list ) {
        error("direct address table is full!\n");
        return -1;
    }
    iaddr = *addr;
    mask_addr(&iaddr, mask, sizeof(iaddr));
    s = strdup(inet_ntoa(iaddr));
    debug("adding direct addr entry: %s%s/%s\n",
          negative? "!": "", s, inet_ntoa(*mask));
    free(s);
    memcpy( &direct_addr_list[n_direct_addr_list].addr,
            &iaddr, sizeof(iaddr));
    memcpy( &direct_addr_list[n_direct_addr_list].mask,
            mask, sizeof(*mask));
    direct_addr_list[n_direct_addr_list].name = NULL;
    direct_addr_list[n_direct_addr_list].negative = negative;
    n_direct_addr_list++;
    return 0;
}
