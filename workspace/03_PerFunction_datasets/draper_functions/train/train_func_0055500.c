clip_call_fill_path(clip_callback_data_t * pccd, int xc, int yc, int xec, int yec)
{
    gx_device *tdev = pccd->tdev;
    dev_proc_fill_path((*proc));
    int code;
    gx_clip_path cpath_intersection;
    gx_clip_path *pcpath = (gx_clip_path *)pccd->pcpath;

    if (pcpath != NULL) {
        gx_path rect_path;
        code = gx_cpath_init_local_shared(&cpath_intersection, pcpath, pccd->ppath->memory);
        if (code < 0)
            return code;
        gx_path_init_local(&rect_path, pccd->ppath->memory);
        gx_path_add_rectangle(&rect_path, int2fixed(xc), int2fixed(yc), int2fixed(xec), int2fixed(yec));
        code = gx_cpath_intersect(&cpath_intersection, &rect_path,
                                  gx_rule_winding_number, (gs_imager_state *)(pccd->pis));
        gx_path_free(&rect_path, "clip_call_fill_path");
    } else {
        gs_fixed_rect clip_box;
        clip_box.p.x = int2fixed(xc);
        clip_box.p.y = int2fixed(yc);
        clip_box.q.x = int2fixed(xec);
        clip_box.q.y = int2fixed(yec);
        gx_cpath_init_local(&cpath_intersection, pccd->ppath->memory);
        code = gx_cpath_from_rectangle(&cpath_intersection, &clip_box);
    }
    if (code < 0)
        return code;
    proc = dev_proc(tdev, fill_path);
    if (proc == NULL)
        proc = gx_default_fill_path;
    code = (*proc)(pccd->tdev, pccd->pis, pccd->ppath, pccd->params,
                   pccd->pdcolor, &cpath_intersection);
    gx_cpath_free(&cpath_intersection, "clip_call_fill_path");
    return code;
}
