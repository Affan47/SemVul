psw_close(gx_device * dev)
{
    gx_device_vector *const vdev = (gx_device_vector *)dev;
    gx_device_pswrite *const pdev = (gx_device_pswrite *)vdev;

    gs_free_object(pdev->v_memory, pdev->image_writer,
                   "psw_close(image_writer)");
    pdev->image_writer = 0;

    if (vdev->strm != NULL) {
        int code = psw_close_printer(dev);

        if (code < 0)
            return code;
    }

    return 0;
}
