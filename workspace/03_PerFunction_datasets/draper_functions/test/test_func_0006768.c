Fb_fill_region(Fb_fill_state_t * pfs, const gs_fixed_rect *rect)
{
    patch_fill_state_t pfs1;
    patch_curve_t curve[4];
    Fb_frame_t * fp = &pfs->frame;
    int code;

    if (VD_TRACE_FUNCTIONAL_PATCH && vd_allowed('s')) {
        vd_get_dc('s');
        vd_set_shift(0, 0);
        vd_set_scale(0.01);
        vd_set_origin(0, 0);
    }
    memcpy(&pfs1, (shading_fill_state_t *)pfs, sizeof(shading_fill_state_t));
    pfs1.Function = pfs->psh->params.Function;
    code = init_patch_fill_state(&pfs1);
    if (code < 0)
        return code;
    pfs1.maybe_self_intersecting = false;
    pfs1.n_color_args = 2;
    pfs1.rect = *rect;
    gs_point_transform2fixed(&pfs->ptm, fp->region.p.x, fp->region.p.y, &curve[0].vertex.p);
    gs_point_transform2fixed(&pfs->ptm, fp->region.q.x, fp->region.p.y, &curve[1].vertex.p);
    gs_point_transform2fixed(&pfs->ptm, fp->region.q.x, fp->region.q.y, &curve[2].vertex.p);
    gs_point_transform2fixed(&pfs->ptm, fp->region.p.x, fp->region.q.y, &curve[3].vertex.p);
    make_other_poles(curve);
    curve[0].vertex.cc[0] = fp->region.p.x;   curve[0].vertex.cc[1] = fp->region.p.y;
    curve[1].vertex.cc[0] = fp->region.q.x;   curve[1].vertex.cc[1] = fp->region.p.y;
    curve[2].vertex.cc[0] = fp->region.q.x;   curve[2].vertex.cc[1] = fp->region.q.y;
    curve[3].vertex.cc[0] = fp->region.p.x;   curve[3].vertex.cc[1] = fp->region.q.y;
    code = patch_fill(&pfs1, curve, NULL, NULL);
    if (term_patch_fill_state(&pfs1))
        return_error(gs_error_unregistered);
    if (VD_TRACE_FUNCTIONAL_PATCH && vd_allowed('s'))
        vd_release_dc;
    return code;
}
