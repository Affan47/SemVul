initialize_crut(void)
{
    memset(&crut_tests, 0, sizeof(crut_tests));


    crut_event_state = 0;

    if (init_context_filename() == NULL) {
	goto abort;
    }

    crut_initialized = 1;

    return;

abort:
    exit(-1);
}
