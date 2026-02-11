make_mcde_default(gx_device *dev, const gs_imager_state *pis,
                  const gs_matrix *pmat, const gs_image_common_t *pic,
                  const gs_int_rect *prect, const gx_drawing_color *pdcolor,
                  const gx_clip_path *pcpath, gs_memory_t *mem,
                  gx_image_enum_common_t **pinfo,
                  gx_device **pmcdev, gx_device *midev,
                  gx_image_enum_common_t *pminfo,
                  const gs_int_point *origin)
{
    gx_device_memory *const mdev = (gx_device_memory *)midev;
    gx_device_mask_clip *mcdev =
        gs_alloc_struct(mem, gx_device_mask_clip, &st_device_mask_clip,
                        "make_mcde_default");
    gx_strip_bitmap bits;
    int code;

    if (mcdev == 0)
        return_error(gs_error_VMerror);
    bits.data = mdev->base;
    bits.raster = mdev->raster;
    bits.size.x = mdev->width;
    bits.size.y = mdev->height;
    bits.id = gx_no_bitmap_id;
    bits.num_planes = 1;
    code = gx_mask_clip_initialize(mcdev, &gs_mask_clip_device,
                                   (const gx_bitmap *)&bits, dev,
                                   origin->x, origin->y, mem);
    if (code < 0) {
        gs_free_object(mem, mcdev, "make_mcde_default");
        return code;
    }
    mcdev->tiles = bits;
    code = dev_proc(mcdev, begin_typed_image)
        ((gx_device *)mcdev, pis, pmat, pic, prect, pdcolor, pcpath, mem,
         pinfo);
    if (code < 0) {
        gs_free_object(mem, mcdev, "make_mcde_default");
        return code;
    }
    *pmcdev = (gx_device *)mcdev;
    return 0;
}
