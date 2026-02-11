cmd_put_range_op(gx_device_clist_writer * cldev, int band_min, int band_max,
                 uint size)
{
    if_debug4m('L', cldev->memory, "[L]band range(%d,%d): size=%u, left=%u",
               band_min, band_max, size, 0);
    if (cldev->ccl != 0 &&
        (cldev->ccl != &cldev->band_range_list ||
         band_min != cldev->band_range_min ||
         band_max != cldev->band_range_max)
        ) {
        if ((cldev->error_code = cmd_write_buffer(cldev, cmd_opv_end_run)) != 0) {
            if (cldev->error_code < 0)
                cldev->error_is_retryable = 0;
            else {

                cldev->error_code = gs_error_VMerror;
                cldev->error_is_retryable = 1;
            }
            return 0;
        }
        cldev->band_range_min = band_min;
        cldev->band_range_max = band_max;
    }
    return cmd_put_list_op(cldev, &cldev->band_range_list, size);
}
