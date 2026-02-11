start_async_event_thread(void)
{

    mca_btl_openib_component.error_counter = 0;


    if(pipe(mca_btl_openib_component.async_pipe)) {
        BTL_ERROR(("Failed to create pipe for communication with "
                    "async event thread"));
        return OMPI_ERROR;
    }

    if(pipe(mca_btl_openib_component.async_comp_pipe)) {
        BTL_ERROR(("Failed to create comp pipe for communication with "
                    "main thread"));
        return OMPI_ERROR;
    }


    if(pthread_create(&mca_btl_openib_component.async_thread, NULL,
                (void*(*)(void*))btl_openib_async_thread, NULL)) {
        BTL_ERROR(("Failed to create async event thread"));
        return OMPI_ERROR;
    }

    return OMPI_SUCCESS;
}
