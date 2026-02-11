ompi_rte_wait_for_debugger(void)
{
    int debugger;
    orte_rml_recv_cb_t xfer;


    debugger = orte_in_parallel_debugger;

    if (1 == MPIR_being_debugged) {
        debugger = 1;
    }

    if (!debugger) {

        return;
    }


    ompi_debugger_setup_dlls();

    if (orte_standalone_operation) {

        while (MPIR_debug_gate == 0) {
#if defined(HAVE_USLEEP)
            usleep(100000);
#else
            sleep(1);
#endif
        }
    } else {


        if (0 != ORTE_PROC_MY_NAME->vpid) {
            return;
        }


        OBJ_CONSTRUCT(&xfer, orte_rml_recv_cb_t);
        xfer.active = true;
        orte_rml.recv_buffer_nb(OMPI_NAME_WILDCARD,
                                ORTE_RML_TAG_DEBUGGER_RELEASE,
                                ORTE_RML_NON_PERSISTENT,
                                orte_rml_recv_callback, &xfer);

        OMPI_WAIT_FOR_COMPLETION(xfer.active);
    }
}
