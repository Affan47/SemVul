gx_psconcretize_CIEABC(const gs_client_color * pc, const gs_color_space * pcs,
                      frac * pconc, const gs_imager_state * pis)
{
    const gs_cie_abc *pcie = pcs->params.abc;
    cie_cached_vector3 vec3;
    int code;

    if_debug3m('c', pis->memory, "[c]concretize CIEABC [%g %g %g]\n",
               pc->paint.values[0], pc->paint.values[1],
               pc->paint.values[2]);
    code = gx_cie_check_rendering_inline(pcs, pconc, pis);
    if (code < 0)
        return code;
    if (code == 1)
        return 0;

    vec3.u = float2cie_cached(pc->paint.values[0]);
    vec3.v = float2cie_cached(pc->paint.values[1]);
    vec3.w = float2cie_cached(pc->paint.values[2]);
    if (!pis->cie_joint_caches->skipDecodeABC)
        cie_lookup_map3(&vec3 , &pcie->caches.DecodeABC,
                        "Decode/MatrixABC");
    GX_CIE_REMAP_FINISH(vec3, pconc, pis, pcs);
    return 0;
}
