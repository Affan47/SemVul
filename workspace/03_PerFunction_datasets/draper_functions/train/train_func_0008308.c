globus_l_seg_activate(void)
{
    int                                 rc;

    rc = globus_module_activate(GLOBUS_COMMON_MODULE);

    if (rc != GLOBUS_SUCCESS)
    {
        goto error;
    }

    globus_l_seg_extension = NULL;
    globus_l_seg_timestamp = 0;
    globus_l_seg_fault_handler = NULL;
    globus_l_seg_fault_arg = NULL;
    globus_l_seg_event_handler = NULL;
    globus_l_seg_event_arg = NULL;

    globus_mutex_init(&globus_l_seg_mutex, NULL);
error:
    return rc;
}
