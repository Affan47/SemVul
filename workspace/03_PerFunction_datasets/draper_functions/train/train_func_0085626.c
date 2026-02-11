pdf_remember_clip_path(gx_device_pdf * pdev, const gx_clip_path * pcpath)
{

    if (pdev->clip_path != 0) {
        gx_path_free(pdev->clip_path, "pdf clip path");
    }
    if (pcpath == 0) {
        pdev->clip_path = 0;
        return 0;
    }
    pdev->clip_path = gx_path_alloc(pdev->pdf_memory, "pdf clip path");
    if (pdev->clip_path == 0)
        return_error(gs_error_VMerror);
    return gx_cpath_to_path((gx_clip_path *)pcpath, pdev->clip_path);
}
