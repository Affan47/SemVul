component_find_check (const char *framework_name, char **requested_component_names, opal_list_t *components)
{
    mca_base_component_list_item_t *cli;
    int i;

    for (i = 0; NULL != requested_component_names &&
             NULL != requested_component_names[i]; ++i) {
        bool found = false;

        OPAL_LIST_FOREACH(cli, components, mca_base_component_list_item_t) {
            if (0 == strcmp(requested_component_names[i],
                            cli->cli_component->mca_component_name)) {
                found = true;
                break;
            }
        }

        if (!found) {
            char h[MAXHOSTNAMELEN];
            gethostname(h, sizeof(h));
            opal_show_help("help-mca-base.txt",
                           "find-available:not-valid", true,
                           h, framework_name, requested_component_names[i]);
            return OPAL_ERR_NOT_FOUND;
        }
    }

    return OPAL_SUCCESS;
}
