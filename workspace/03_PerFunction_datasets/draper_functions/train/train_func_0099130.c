globus_l_seg_stdout_deactivate(void)
{
    globus_mutex_lock(&globus_l_seg_mutex);
    globus_l_seg_shutdown = 1;

    if (globus_l_seg_write_registered)
    {
        while (globus_l_seg_shutdown == 1)
        {
            globus_cond_wait(&globus_l_seg_cond, &globus_l_seg_mutex);
        }
    }
    globus_fifo_destroy(&globus_l_seg_buffers);
    globus_mutex_unlock(&globus_l_seg_mutex);

    globus_xio_close(globus_l_seg_output_handle, NULL);
    globus_xio_close(globus_l_seg_input_handle, NULL);

    globus_mutex_destroy(&globus_l_seg_mutex);
    globus_cond_destroy(&globus_l_seg_cond);

    globus_module_deactivate(GLOBUS_XIO_MODULE);
    globus_module_deactivate(GLOBUS_SCHEDULER_EVENT_GENERATOR_MODULE);
    globus_module_deactivate(GLOBUS_COMMON_MODULE);

    return 0;
}
