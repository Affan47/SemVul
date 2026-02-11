zsetdevicecolorrendering1(i_ctx_t *i_ctx_p)
{
    os_ptr op = osp;
    int code;
    ref_cie_render_procs procs;

    check_type(op[-1], t_dictionary);
    check_stype(*op, st_cie_render1);
    code = gs_setcolorrendering(igs, r_ptr(op, gs_cie_render));
    if (code < 0)
        return code;
    refset_null((ref *)&procs, sizeof(procs) / sizeof(ref));
    if (gs_cie_cs_common(igs) != 0 &&
        (code = cie_cache_joint(i_ctx_p, &procs, gs_cie_cs_common(igs), igs)) < 0
        )
        return code;
    istate->colorrendering.dict = op[-1];
    refset_null((ref *)&istate->colorrendering.procs,
                sizeof(istate->colorrendering.procs) / sizeof(ref));
    pop(2);
    return 0;
}
