gx_cie_check_rendering_inline(const gs_color_space * pcs, frac * pconc, const gs_imager_state * pis)
{
    if (pis->cie_render == 0 && !pis->cie_to_xyz) {

        pconc[0] = pconc[1] = pconc[2] = frac_0;
        return 1;
    }
    if (pis->cie_joint_caches->status == CIE_JC_STATUS_COMPLETED) {
        if (pis->cie_joint_caches->cspace_id != pcs->id)
            pis->cie_joint_caches->status = CIE_JC_STATUS_BUILT;
    }
    if (pis->cie_joint_caches->status != CIE_JC_STATUS_COMPLETED) {
        int     code = gs_cie_jc_complete(pis, pcs);

        if (code < 0)
            return code;
    }
    return 0;
}
