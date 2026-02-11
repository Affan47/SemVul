get_remote_node_uuid(cib_t * the_cib, const char *uname, char **uuid)
{
#define REMOTE_NODE_XPATH "//nvpair[@name='remote-node'][@value='%s']"
#define REMOTE_NODE_XPATH2 "//primitive[@type='remote'][@provider='pacemaker'][@id='%s']"
    int rc = pcmk_ok;
    char *xpath_string = NULL;
    size_t len = strlen(REMOTE_NODE_XPATH) + strlen(uname) + 1;
    xmlNode *xml_search = NULL;

    xpath_string = calloc(1, len);
    sprintf(xpath_string, REMOTE_NODE_XPATH, uname);
    rc = cib_internal_op(the_cib, CIB_OP_QUERY, NULL, xpath_string, NULL, &xml_search,
                         cib_sync_call | cib_scope_local | cib_xpath, NULL);
    free(xpath_string);
    free(xml_search);

    if (rc != pcmk_ok) {
        len = strlen(REMOTE_NODE_XPATH2) + strlen(uname) + 1;
        xpath_string = calloc(1, len);
        sprintf(xpath_string, REMOTE_NODE_XPATH2, uname);
        rc = cib_internal_op(the_cib, CIB_OP_QUERY, NULL, xpath_string, NULL, &xml_search,
                             cib_sync_call | cib_scope_local | cib_xpath, NULL);

        free(xpath_string);
        free(xml_search);
    }

    if (rc == pcmk_ok) {
        *uuid = strdup(uname);
    }

    return rc;
}
