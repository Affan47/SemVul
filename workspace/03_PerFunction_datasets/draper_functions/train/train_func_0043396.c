ISNSDisplay_Node ( SOIP_Node *p_node )
{
    int ii;

    __LOG_INFO ("******************** NODE RECORD **************\n");
    ISNSDisplay_Node_Name (&p_node->node_name);

    for (ii = 0; ii < NODE_SYM_NAME_SIZE; ii++)
       if (p_node->sym_name[ii] == (char)SNS_UNREGISTERED)
          p_node->sym_name[ii] = '\0';
    __LOG_INFO ("Symbolic Node Name  : %s      \n",  p_node->sym_name);

    ISNSDisplay_NodeIPA (&p_node->node_ipa);

    ISNSDisplay_IPAddress (&p_node->ip_addr);

    __LOG_INFO ("Port map            : %08X      \n",  p_node->port_map);
    for (ii = 0; ii < MAX_PORTS_PER_NODE; ii++)
       if (p_node->port_map & (1 << ii))
          ISNSDisplay_Port_Name (&p_node->port_name[ii], p_name);

    __LOG_INFO ("***********************************************\n");
}
