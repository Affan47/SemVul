gx_concrete_space_CIE(const gs_color_space * pcs, const gs_imager_state * pis)
{
    const gs_cie_render *pcie = pis->cie_render;

    if (pcie == 0 || pcie->RenderTable.lookup.table == 0 ||
        pcie->RenderTable.lookup.m == 3
        ) {
        return pis->devicergb_cs;
    } else {
        return pis->devicecmyk_cs;
    }
}
