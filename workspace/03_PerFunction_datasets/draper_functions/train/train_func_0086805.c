udpTable_next_entry( void **loop_context,
                     void **data_context,
                     netsnmp_variable_list *index,
                     netsnmp_iterator_info *data)
{
    UDPTABLE_ENTRY_TYPE	 *entry = (UDPTABLE_ENTRY_TYPE *)*loop_context;
    long port;
    long addr;

    if (!entry)
        return NULL;


#if defined(osf5) && defined(IN6_EXTRACT_V4ADDR)
                snmp_set_var_value(index,
                              (u_char*)&IN6_EXTRACT_V4ADDR(&entry->pcb.inp_laddr),
                                 sizeof(IN6_EXTRACT_V4ADDR(&entry->pcb.inp_laddr)));
#else
    addr = UDP_ADDRESS_TO_NETWORK_ORDER((in_addr_t)entry->UDPTABLE_LOCALADDRESS);
    snmp_set_var_value(index, (u_char *)&addr,
                                 sizeof(addr));
#endif
    port = UDP_PORT_TO_HOST_ORDER(entry->UDPTABLE_LOCALPORT);
    snmp_set_var_value(index->next_variable,
                               (u_char*)&port, sizeof(port));


    *data_context = (void*)entry;
    *loop_context = (void*)entry->INP_NEXT_SYMBOL;
    return index;
}
