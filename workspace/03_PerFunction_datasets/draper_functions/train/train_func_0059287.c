orte_oob_base_get_addr(char **uri)
{
    char *turi, *final=NULL, *tmp;
    size_t len = 0;
    int rc=ORTE_SUCCESS;
    bool one_added = false;
    mca_base_component_list_item_t *cli;
    mca_oob_base_component_t *component;


    if (ORTE_SUCCESS != (rc = orte_util_convert_process_name_to_string(&final, ORTE_PROC_MY_NAME))) {
        ORTE_ERROR_LOG(rc);
        goto unblock;
    }
    len = strlen(final);


    OPAL_LIST_FOREACH(cli, &orte_oob_base.actives, mca_base_component_list_item_t) {
        component = (mca_oob_base_component_t*)cli->cli_component;


        if (NULL == component->get_addr) {

            continue;
        }


        turi = component->get_addr();

        if (0 < orte_oob_base.max_uri_length &&
            orte_oob_base.max_uri_length < (int)(len + strlen(turi))) {

            continue;
        }

        asprintf(&tmp, "%s;%s", final, turi);
        free(turi);
        free(final);
        final = tmp;
        len = strlen(final);

        one_added = true;
    }

    if (!one_added) {

        if (NULL != final) {
            free(final);
            final = NULL;
        }
    }

 unblock:
    *uri = final;
}
