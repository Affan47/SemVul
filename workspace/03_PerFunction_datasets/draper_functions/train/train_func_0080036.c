psw_open(gx_device * dev)
{
    gs_memory_t *mem = gs_memory_stable(dev->memory);
    gx_device_vector *const vdev = (gx_device_vector *)dev;
    gx_device_pswrite *const pdev = (gx_device_pswrite *)vdev;

    vdev->v_memory = mem;
    vdev->vec_procs = &psw_vector_procs;

    gdev_vector_init(vdev);
    vdev->fill_options = vdev->stroke_options = gx_path_type_optimize;
    pdev->binary_ok = !pdev->params.ASCII85EncodePages;
    pdev->image_writer = gs_alloc_struct(mem, psdf_binary_writer,
                                         &st_psdf_binary_writer,
                                         "psw_open(image_writer)");
    memset(pdev->image_writer, 0, sizeof(*pdev->image_writer));
    image_cache_reset(pdev);

    pdev->strm = NULL;


    {
        int code = psw_open_printer(dev);

        if (code < 0)
            return code;
    }

    return 0;
}
