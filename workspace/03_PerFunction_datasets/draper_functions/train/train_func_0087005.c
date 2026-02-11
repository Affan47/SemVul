finalize(void)
{
    opal_list_item_t* item;
    orte_iof_write_output_t *output;
    orte_iof_write_event_t *wev;
    int num_written;
    bool dump;
    int i;
    orte_job_t *jdata;


    wev = orte_iof_base.iof_write_stdout->wev;
    if (!opal_list_is_empty(&wev->outputs)) {
        dump = false;

        while (NULL != (item = opal_list_remove_first(&wev->outputs))) {
            output = (orte_iof_write_output_t*)item;
            if (!dump) {
                num_written = write(wev->fd, output->data, output->numbytes);
                if (num_written < output->numbytes) {

                    dump = true;
                }
            }
            OBJ_RELEASE(output);
        }
    }
    if (!orte_xml_output) {

        wev = orte_iof_base.iof_write_stderr->wev;
        if (!opal_list_is_empty(&wev->outputs)) {
            dump = false;

            while (NULL != (item = opal_list_remove_first(&wev->outputs))) {
                output = (orte_iof_write_output_t*)item;
                if (!dump) {
                    num_written = write(wev->fd, output->data, output->numbytes);
                    if (num_written < output->numbytes) {

                        dump = true;
                    }
                }
                OBJ_RELEASE(output);
            }
        }
    }

    orte_rml.recv_cancel(ORTE_NAME_WILDCARD, ORTE_RML_TAG_IOF_HNP);


    for (i=0; i < mca_iof_mr_hnp_component.stdin_jobs.size; i++) {
        if (NULL == (jdata = (orte_job_t*)opal_pointer_array_get_item(&mca_iof_mr_hnp_component.stdin_jobs, i))) {
            continue;
        }
        OBJ_RELEASE(jdata);
    }
    OBJ_DESTRUCT(&mca_iof_mr_hnp_component.stdin_jobs);

    return ORTE_SUCCESS;
}
