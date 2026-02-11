orte_oob_base_set_addr(int fd, short args, void *cbdata)
{
    mca_oob_uri_req_t *req = (mca_oob_uri_req_t*)cbdata;
    char *uri = req->uri;

    opal_output_verbose(5, orte_oob_base_framework.framework_output,
                        "%s: set_addr to uri %s",
                        ORTE_NAME_PRINT(ORTE_PROC_MY_NAME),
                        (NULL == uri) ? "NULL" : uri);


    if (NULL == uri) {
        opal_output(0, "%s: NULL URI", ORTE_NAME_PRINT(ORTE_PROC_MY_NAME));
        ORTE_FORCED_TERMINATE(1);
        OBJ_RELEASE(req);
        return;
    }

    process_uri(uri);
    OBJ_RELEASE(req);
}
