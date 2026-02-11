recv_ack(int status, orte_process_name_t* sender,
                     opal_buffer_t* buffer, orte_rml_tag_t tag,
                     void* cbdata)
{
    opal_list_item_t *item, *itm;
    orte_filem_raw_outbound_t *outbound;
    orte_filem_raw_xfer_t *xfer;
    char *file;
    int st, n, rc;


    n=1;
    if (OPAL_SUCCESS != (rc = opal_dss.unpack(buffer, &file, &n, OPAL_STRING))) {
        ORTE_ERROR_LOG(rc);
        return;
    }


    n=1;
    if (OPAL_SUCCESS != (rc = opal_dss.unpack(buffer, &st, &n, OPAL_INT))) {
        ORTE_ERROR_LOG(rc);
        return;
    }

    OPAL_OUTPUT_VERBOSE((1, orte_filem_base_framework.framework_output,
                         "%s filem:raw: recvd ack from %s for file %s status %d",
                         ORTE_NAME_PRINT(ORTE_PROC_MY_NAME),
                         ORTE_NAME_PRINT(sender), file, st));


    for (item = opal_list_get_first(&outbound_files);
         item != opal_list_get_end(&outbound_files);
         item = opal_list_get_next(item)) {
        outbound = (orte_filem_raw_outbound_t*)item;
        for (itm = opal_list_get_first(&outbound->xfers);
             itm != opal_list_get_end(&outbound->xfers);
             itm = opal_list_get_next(itm)) {
            xfer = (orte_filem_raw_xfer_t*)itm;
            if (0 == strcmp(file, xfer->file)) {

                if (0 != st) {
                    xfer->status = st;
                }

                xfer->nrecvd++;

                if (xfer->nrecvd == orte_process_info.num_procs) {
                    OPAL_OUTPUT_VERBOSE((1, orte_filem_base_framework.framework_output,
                                         "%s filem:raw: xfer complete for file %s status %d",
                                         ORTE_NAME_PRINT(ORTE_PROC_MY_NAME),
                                         file, xfer->status));
                    xfer_complete(xfer->status, xfer);
                }
                free(file);
                return;
            }
        }
    }
}
