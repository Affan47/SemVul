parse_dash_host(char ***mapped_nodes, char** host_argv)
{
    orte_std_cntr_t j, k;
    int rc=ORTE_SUCCESS;
    char **mini_map, *cptr;
    int nodeidx;
    orte_node_t *node;


    for (j = 0; j < opal_argv_count(host_argv); ++j) {
        mini_map = opal_argv_split(host_argv[j], ',');

        for (k = 0; NULL != mini_map[k]; ++k) {
            if ('+' == mini_map[k][0]) {

                if ('e' == mini_map[k][1] ||
                    'E' == mini_map[k][1]) {


                    if (NULL != (cptr = strchr(mini_map[k], ':'))) {

                        *cptr = '*';
                        opal_argv_append_nosize(mapped_nodes, cptr);
                    } else {

                        opal_argv_append_nosize(mapped_nodes, "*");
                    }
                } else if ('n' == mini_map[k][1] ||
                           'N' == mini_map[k][1]) {


                    nodeidx = strtol(&mini_map[k][2], NULL, 10);
                    if (nodeidx < 0 ||
                        nodeidx > (int)orte_node_pool->size) {

                        orte_show_help("help-dash-host.txt", "dash-host:relative-node-out-of-bounds",
                                       true, nodeidx, mini_map[k]);
                        rc = ORTE_ERR_SILENT;
                        goto cleanup;
                    }


                    if (!orte_hnp_is_allocated) {
                        nodeidx++;
                    }


                    if (NULL == (node = (orte_node_t *) opal_pointer_array_get_item(orte_node_pool, nodeidx))) {

                        orte_show_help("help-dash-host.txt", "dash-host:relative-node-not-found",
                                       true, nodeidx, mini_map[k]);
                        rc = ORTE_ERR_SILENT;
                        goto cleanup;
                    }

                    opal_argv_append_nosize(mapped_nodes, node->name);
                } else {

                    orte_show_help("help-dash-host.txt", "dash-host:invalid-relative-node-syntax",
                                   true, mini_map[k]);
                    rc = ORTE_ERR_SILENT;
                    goto cleanup;
                }
            } else {
                if (OPAL_SUCCESS != (rc = opal_argv_append_nosize(mapped_nodes,
                                                                  mini_map[k]))) {
                    goto cleanup;
                }
            }
        }
        opal_argv_free(mini_map);
        mini_map = NULL;
    }

cleanup:
    if (NULL != mini_map) {
        opal_argv_free(mini_map);
    }
    return rc;
}
