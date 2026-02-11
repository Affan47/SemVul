gdev_prn_tear_down(gx_device *pdev, byte **the_memory)
{
    gx_device_printer * const ppdev = (gx_device_printer *)pdev;
    gx_device_memory * const pmemdev = (gx_device_memory *)pdev;
    gx_device_clist *const pclist_dev = (gx_device_clist *)pdev;
    gx_device_clist_common * const pcldev = &pclist_dev->common;
    gx_device_clist_reader * const pcrdev = &pclist_dev->reader;
    bool was_command_list;

    if (PRINTER_IS_CLIST(ppdev)) {

        (*gs_clist_device_procs.close_device)( (gx_device *)pcldev );
        *the_memory = ppdev->buf;
        ppdev->buf = 0;
        ppdev->buffer_space = 0;
        was_command_list = true;


        if (!CLIST_IS_WRITER(pclist_dev))
            gs_free_object(pcrdev->memory, pcrdev->color_usage_array, "clist_color_usage_array");

    } else {

        *the_memory = pmemdev->base;
        pmemdev->base = 0;
        was_command_list = false;
    }


    if (ppdev->orig_procs.open_device != 0)
        pdev->procs = ppdev->orig_procs;
    ppdev->orig_procs.open_device = 0;

    return was_command_list;
}
