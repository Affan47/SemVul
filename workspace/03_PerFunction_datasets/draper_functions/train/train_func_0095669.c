group_requests(netsnmp_agent_request_info *agtreq_info,
               netsnmp_request_info *requests,
               netsnmp_container *request_group, table_container_data * tad)
{
    netsnmp_table_request_info *tblreq_info;
    netsnmp_index *row, *tmp, index;
    netsnmp_request_info *current;
    netsnmp_request_group *g;
    netsnmp_request_group_item *i;

    for (current = requests; current; current = current->next) {


        if (current->processed != 0) {
            DEBUGMSGTL(("table_array:group",
                        "already processed\n"));
            continue;
        }


        row = NULL;
        tblreq_info = netsnmp_extract_table_info(current);
        netsnmp_assert(tblreq_info->colnum <= tad->tblreg_info->max_column);


        index.oids = tblreq_info->index_oid;
        index.len = tblreq_info->index_oid_len;
        tmp = (netsnmp_index*)CONTAINER_FIND(request_group, &index);
        if (tmp) {
            DEBUGMSGTL(("table_array:group",
                        "    existing group:"));
            DEBUGMSGOID(("table_array:group", index.oids,
                         index.len));
            DEBUGMSG(("table_array:group", "\n"));
            g = (netsnmp_request_group *) tmp;
            i = SNMP_MALLOC_TYPEDEF(netsnmp_request_group_item);
            if (i == NULL)
                return;
            i->ri = current;
            i->tri = tblreq_info;
            i->next = g->list;
            g->list = i;


            continue;
        }

        DEBUGMSGTL(("table_array:group", "    new group"));
        DEBUGMSGOID(("table_array:group", index.oids,
                     index.len));
        DEBUGMSG(("table_array:group", "\n"));
        g = SNMP_MALLOC_TYPEDEF(netsnmp_request_group);
        i = SNMP_MALLOC_TYPEDEF(netsnmp_request_group_item);
        if (i == NULL || g == NULL) {
            SNMP_FREE(i);
            SNMP_FREE(g);
            return;
        }
        g->list = i;
        g->table = tad->table;
        i->ri = current;
        i->tri = tblreq_info;


        row = g->existing_row = (netsnmp_index*)CONTAINER_FIND(tad->table, &index);
        if (!g->existing_row) {
            if (!tad->cb->create_row) {
#ifndef NETSNMP_NO_WRITE_SUPPORT
                if(MODE_IS_SET(agtreq_info->mode))
                    netsnmp_set_request_error(agtreq_info, current,
                                              SNMP_ERR_NOTWRITABLE);
                else
#endif
                    netsnmp_set_request_error(agtreq_info, current,
                                              SNMP_NOSUCHINSTANCE);
                free(g);
                free(i);
                continue;
            }

            row = g->existing_row = tad->cb->create_row(&index);
            if (!row) {


                netsnmp_set_request_error(agtreq_info, current,
                                          SNMP_ERR_GENERR);
                free(g);
                free(i);
                continue;
            }
            g->row_created = 1;
        }

        g->index.oids = row->oids;
        g->index.len = row->len;

        CONTAINER_INSERT(request_group, g);

    }
}
