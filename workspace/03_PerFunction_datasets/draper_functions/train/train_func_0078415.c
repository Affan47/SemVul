set_network_defaults(WAPEvent **e, long type_of_address)
{
    gw_assert(type_of_address == ADDR_USER || type_of_address == ADDR_PLMN ||
              type_of_address == ADDR_IPV4 || type_of_address == ADDR_IPV6 ||
              type_of_address == ADDR_WINA);

    if ((*e)->type != Push_Message)
        return;

    (*e)->u.Push_Message.network_required = PAP_TRUE;
    octstr_destroy((*e)->u.Push_Message.network);

    switch (type_of_address) {
    case ADDR_PLMN:
	(*e)->u.Push_Message.network = octstr_format("%s", "GSM");
    break;

    case ADDR_IPV4:
        (*e)->u.Push_Message.network = octstr_format("%s", "GSM");
    break;

    case ADDR_IPV6:
    break;
    }
}
