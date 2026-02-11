ppm_set_dev_procs(gx_device * pdev)
{
    gx_device_pbm * const bdev = (gx_device_pbm *)pdev;

    if (dev_proc(pdev, copy_alpha) != pnm_copy_alpha) {
        bdev->save_copy_alpha = dev_proc(pdev, copy_alpha);
        if (pdev->color_info.depth > 4)
            set_dev_proc(pdev, copy_alpha, pnm_copy_alpha);
    }
    if (dev_proc(pdev, begin_typed_image) != pnm_begin_typed_image) {
        bdev->save_begin_typed_image = dev_proc(pdev, begin_typed_image);
        set_dev_proc(pdev, begin_typed_image, pnm_begin_typed_image);
    }
    if (bdev->color_info.num_components == 4) {
        if (bdev->color_info.depth == 4) {
            set_dev_proc(pdev, map_color_rgb, cmyk_1bit_map_color_rgb);
            set_dev_proc(pdev, map_cmyk_color, cmyk_1bit_map_cmyk_color);
        } else if (bdev->magic == 7) {
            set_dev_proc(pdev, map_color_rgb, cmyk_8bit_map_color_rgb);
            set_dev_proc(pdev, map_cmyk_color, cmyk_8bit_map_cmyk_color);
        } else {
            set_dev_proc(pdev, map_color_rgb, pkm_map_color_rgb);
            set_dev_proc(pdev, map_cmyk_color, pkm_map_cmyk_color);
        }
    }
}
