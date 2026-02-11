orte_util_add_dash_host_nodes(opal_list_t *nodes,
                                  char ** host_argv)
{
    opal_list_item_t* item;
    orte_std_cntr_t i, j, k;
    int rc;
    char **mapped_nodes = NULL, **mini_map;
    orte_node_t *node;


    for (j = 0; j < opal_argv_count(host_argv); ++j) {
        mini_map = opal_argv_split(host_argv[j], ',');

        if (mapped_nodes == NULL) {
            mapped_nodes = mini_map;
        } else {
            for (k = 0; NULL != mini_map[k]; ++k) {
                rc = opal_argv_append_nosize(&mapped_nodes,
                                             mini_map[k]);
                if (OPAL_SUCCESS != rc) {
                    goto cleanup;
                }
            }
            opal_argv_free(mini_map);
        }
    }


    if (NULL == mapped_nodes) {
        return ORTE_SUCCESS;
    }


    for (i = 0; NULL != mapped_nodes[i]; ++i) {


        if ('+' == mapped_nodes[i][0]) {
            orte_show_help("help-dash-host.txt", "dash-host:relative-syntax",
                           true, mapped_nodes[i]);
            rc = ORTE_ERR_SILENT;
            goto cleanup;
        }


        for (item = opal_list_get_first(nodes);
             item != opal_list_get_end(nodes);
             item = opal_list_get_next(item)) {
            node = (orte_node_t*) item;
            if (0 == strcmp(node->name, mapped_nodes[i]) ||
               (0 == strcmp(node->name, orte_process_info.nodename) &&
               (0 == strcmp(mapped_nodes[i], "localhost") || opal_ifislocal(mapped_nodes[i])))) {
                ++node->slots;

                node->slots_given = true;
                break;
            }
        }


        if (item == opal_list_get_end(nodes)) {
            node = OBJ_NEW(orte_node_t);
            if (NULL == node) {
                return ORTE_ERR_OUT_OF_RESOURCE;
            }

            if (0 == strcmp(mapped_nodes[i], "localhost") ||
                opal_ifislocal(mapped_nodes[i])) {


                if (orte_show_resolved_nodenames &&
                    0 != strcmp(mapped_nodes[i], orte_process_info.nodename)) {

                    opal_argv_append_unique_nosize(&node->alias, mapped_nodes[i], false);
                }
                node->name = strdup(orte_process_info.nodename);
            } else {

                node->name = strdup(mapped_nodes[i]);
            }
            node->state = ORTE_NODE_STATE_UP;
            node->slots_inuse = 0;
            node->slots_max = 0;
            node->slots = 1;

            node->slots_given = true;
            opal_list_append(nodes, &node->super);
        }
    }
    rc = ORTE_SUCCESS;

cleanup:
    if (NULL != mapped_nodes) {
        opal_argv_free(mapped_nodes);
    }

    return rc;
}
