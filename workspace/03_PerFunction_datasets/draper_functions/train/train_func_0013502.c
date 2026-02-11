gs_cspace_build_CIEA(gs_color_space ** ppcspace, void *client_data,
                     gs_memory_t * pmem)
{
    gs_cie_a *pciea =
    gx_build_cie_space(ppcspace, &gs_color_space_type_CIEA, &st_cie_a, pmem);

    if (pciea == 0)
        return_error(gs_error_VMerror);

    gx_set_common_cie_defaults(&pciea->common, client_data);
    pciea->common.install_cspace = gx_install_CIEA;
    pciea->RangeA = RangeA_default;
    pciea->DecodeA = DecodeA_default;
    pciea->MatrixA = MatrixA_default;

    (*ppcspace)->params.a = pciea;
    return 0;
}
