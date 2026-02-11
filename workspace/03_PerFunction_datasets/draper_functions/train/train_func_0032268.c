gfs_l_gfork_xio_setup()
{
    globus_result_t                     result;

    result = globus_xio_attr_init(&g_attr);
    if(result != GLOBUS_SUCCESS)
    {
        goto error_attr_init;
    }
    result = globus_xio_stack_init(&g_stack, NULL);
    if(result != GLOBUS_SUCCESS)
    {
        goto error_stack_init;
    }

    result = globus_xio_driver_load("tcp", &g_tcp_driver);
    if(result != GLOBUS_SUCCESS)
    {
        goto error_tcp;
    }

    result = globus_xio_stack_push_driver(g_stack, g_tcp_driver);
    if(result != GLOBUS_SUCCESS)
    {
        goto error_tcp_push;
    }
    result = globus_xio_attr_cntl(
        g_attr,
        g_tcp_driver,
        GLOBUS_XIO_TCP_SET_PORT,
        g_port);
    if(result != GLOBUS_SUCCESS)
    {
        goto error_port;
    }

    if(g_use_gsi)
    {
        result = globus_xio_driver_load("gsi", &g_gsi_driver);
        if(result != GLOBUS_SUCCESS)
        {
            goto error_gsi;
        }
        result = globus_xio_stack_push_driver(g_stack, g_gsi_driver);
        if(result != GLOBUS_SUCCESS)
        {
            goto error_gsi_push;
        }
        result = globus_xio_attr_cntl(
            g_attr,
            g_gsi_driver,
            GLOBUS_XIO_GSI_SET_AUTHORIZATION_MODE,
            GLOBUS_XIO_GSI_NO_AUTHORIZATION);
        if(result != GLOBUS_SUCCESS)
        {
            goto error_gsi_push;
        }
    }

    return GLOBUS_SUCCESS;

error_gsi_push:
error_gsi:
error_port:
error_tcp_push:
error_tcp:
error_stack_init:
error_attr_init:

    return result;
}
