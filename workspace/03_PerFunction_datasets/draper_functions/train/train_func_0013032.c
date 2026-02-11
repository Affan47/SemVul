clist_render_thread(void *data)
{
    clist_render_thread_control_t *thread = (clist_render_thread_control_t *)data;
    gx_device *dev = thread->cdev;
    gx_device_clist *cldev = (gx_device_clist *)dev;
    gx_device_clist_reader *crdev = &cldev->reader;
    gx_device *bdev = thread->bdev;
    gs_int_rect band_rect;
    byte *mdata = crdev->data + crdev->page_tile_cache_size;
    uint raster = bitmap_raster(dev->width * dev->color_info.depth);
    int code;
    int band_height = crdev->page_band_height;
    int band = thread->band;
    int band_begin_line = band * band_height;
    int band_end_line = band_begin_line + band_height;
    int band_num_lines;
#ifdef DEBUG
    long starttime[2], endtime[2];

    gp_get_usertime(starttime);
#endif
    if (band_end_line > dev->height)
        band_end_line = dev->height;
    band_num_lines = band_end_line - band_begin_line;

    code = crdev->buf_procs.setup_buf_device
            (bdev, mdata, raster, NULL, 0, band_num_lines, band_num_lines);
    band_rect.p.x = 0;
    band_rect.p.y = band_begin_line;
    band_rect.q.x = dev->width;
    band_rect.q.y = band_end_line;
    if (code >= 0)
        code = clist_render_rectangle(cldev, &band_rect, bdev, NULL, true);

    crdev->ymin = band_begin_line;
    crdev->ymax = band_end_line;
    crdev->offset_map = NULL;
    if (code < 0)
        thread->status = THREAD_ERROR;
    else
        thread->status = THREAD_DONE;

#ifdef DEBUG
    gp_get_usertime(endtime);
    thread->cputime += (endtime[0] - starttime[0]) * 1000 +
             (endtime[1] - starttime[1]) / 1000000;
#endif


    gx_semaphore_signal(thread->sema_group);
    gx_semaphore_signal(thread->sema_this);
}
