udpTable_free(netsnmp_cache *cache, void *magic)
{
    UDPTABLE_ENTRY_TYPE	 *p;
    while (udp_head) {
        p = udp_head;
        udp_head = udp_head->INP_NEXT_SYMBOL;
        free(p);
    }

    udp_head = NULL;
}
