globus_l_seg_register_write(
    globus_byte_t *                     buf)
{
    globus_result_t                     result;
    size_t                              cnt;
    globus_xio_iovec_t *                iov;
    size_t                              nbytes=0;
    int                                 i;

    if (buf)
    {
        globus_fifo_enqueue(&globus_l_seg_buffers, buf);
    }

    cnt = globus_fifo_size(&globus_l_seg_buffers);
    if ((!globus_l_seg_write_registered) && cnt > 0)
    {

        iov = globus_libc_calloc(cnt, sizeof(globus_xio_iovec_t));
        if (iov == NULL)
        {
            result = GLOBUS_SEG_ERROR_OUT_OF_MEMORY;

            goto call_fault_handler;
        }

        for (i = 0; i < cnt; i++)
        {
            iov[i].iov_base = globus_fifo_dequeue(&globus_l_seg_buffers);
            iov[i].iov_len = strlen((char *)iov[i].iov_base);
            nbytes += iov[i].iov_len;
        }

        result = globus_xio_register_writev(
                globus_l_seg_output_handle,
                iov,
                cnt,
                nbytes,
                NULL,
                globus_l_seg_writev_callback,
                NULL);

        if (result != GLOBUS_SUCCESS)
        {
            goto call_fault_handler;
        }
        globus_l_seg_write_registered = GLOBUS_TRUE;
    }

    return GLOBUS_SUCCESS;

call_fault_handler:
    globus_scheduler_event_generator_fault(result);

    return result;
}
