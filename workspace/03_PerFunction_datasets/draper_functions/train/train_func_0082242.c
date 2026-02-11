finalize(void)
{
    opal_list_item_t* item;
    orte_iof_write_output_t *output;
    orte_iof_write_event_t *wev;
    int num_written;
    bool dump;


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
    OBJ_RELEASE(orte_iof_base.iof_write_stdout);
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
        OBJ_RELEASE(orte_iof_base.iof_write_stderr);
    }


    orte_rml.recv_cancel(ORTE_NAME_WILDCARD, ORTE_RML_TAG_IOF_PROXY);

    return ORTE_SUCCESS;
}
