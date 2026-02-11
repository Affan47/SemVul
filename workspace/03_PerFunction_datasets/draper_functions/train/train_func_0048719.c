gs_cie_render1_build(gs_cie_render ** ppcrd, gs_memory_t * mem,
                     client_name_t cname)
{
    gs_cie_render *pcrd;

    rc_alloc_struct_1(pcrd, gs_cie_render, &st_cie_render1, mem,
                      return_error(gs_error_VMerror), cname);
    pcrd->id = gs_next_ids(mem, 1);

    pcrd->client_data = 0;
    pcrd->RenderTable.lookup.table = 0;
    pcrd->status = CIE_RENDER_STATUS_BUILT;
    *ppcrd = pcrd;
    return 0;
}
