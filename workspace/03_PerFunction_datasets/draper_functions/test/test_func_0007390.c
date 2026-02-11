gx_forward_begin_typed_image(gx_device * dev, const gs_imager_state * pis,
                             const gs_matrix * pmat,
                             const gs_image_common_t * pim,
                             const gs_int_rect * prect,
                             const gx_drawing_color * pdcolor,
                             const gx_clip_path * pcpath,
                             gs_memory_t * memory,
                             gx_image_enum_common_t ** pinfo)
{
    gx_device_forward * const fdev = (gx_device_forward *)dev;
    gx_device *tdev = fdev->target;
    dev_proc_begin_typed_image((*proc)) =
        (tdev == 0 ? (tdev = dev, gx_default_begin_typed_image) :
         dev_proc(tdev, begin_typed_image));

    return proc(tdev, pis, pmat, pim, prect, pdcolor, pcpath,
                memory, pinfo);
}
