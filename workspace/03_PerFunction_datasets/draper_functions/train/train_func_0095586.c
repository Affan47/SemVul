clj_put_params(
    gx_device *             pdev,
    gs_param_list *         plist
)
{
    float		    mediasize[2];
    bool                    rotate = false;
    int                     have_pagesize = clj_media_size(mediasize, plist);

    if (have_pagesize < 0)
        return have_pagesize;
    if (have_pagesize) {
        if (get_paper_size(mediasize, &rotate) == 0 || rotate)
            return_error(gs_error_rangecheck);
    }
    return gdev_prn_put_params(pdev, plist);
}
