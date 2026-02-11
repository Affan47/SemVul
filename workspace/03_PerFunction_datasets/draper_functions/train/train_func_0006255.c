overprint_sep_fill_rectangle(
    gx_device *     dev,
    int             x,
    int             y,
    int             width,
    int             height,
    gx_color_index  color )
{
    overprint_device_t *    opdev = (overprint_device_t *)dev;
    gx_device *             tdev = opdev->target;

    if (tdev == 0)
        return 0;
    else {
        int     depth = tdev->color_info.depth;


#if !arch_is_big_endian
        if (depth > 8)
            color = swap_color_index(depth, color);
#endif


        if ( depth <= 8 * sizeof(mono_fill_chunk) &&
             (depth & (depth - 1)) == 0 && !(opdev->blendspot))
            return gx_overprint_sep_fill_rectangle_1( tdev,
                                                      opdev->retain_mask,
                                                      x, y, width, height,
                                                      color,
                                                      dev->memory );
        else
            return gx_overprint_sep_fill_rectangle_2( tdev, opdev->blendspot,
                                                      opdev->retain_mask,
                                                      x, y, width, height,
                                                      color,
                                                      dev->memory );
    }
}
