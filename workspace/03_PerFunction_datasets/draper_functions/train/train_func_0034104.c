fn_1ItSg_make_scaled(const gs_function_1ItSg_t *pfn,
                     gs_function_1ItSg_t **ppsfn,
                     const gs_range_t *pranges, gs_memory_t *mem)
{
    gs_function_1ItSg_t *psfn =
        gs_alloc_struct(mem, gs_function_1ItSg_t, &st_function_1ItSg,
                        "fn_1ItSg_make_scaled");
    int code;

    if (psfn == 0)
        return_error(gs_error_VMerror);
    psfn->params = pfn->params;
    psfn->params.Functions = 0;
    psfn->params.Bounds =
        fn_copy_values(pfn->params.Bounds, pfn->params.k - 1, sizeof(float),
                       mem);
    psfn->params.Encode =
        fn_copy_values(pfn->params.Encode, 2 * pfn->params.k, sizeof(float),
                       mem);
    if ((code = (psfn->params.Bounds == 0 || psfn->params.Encode == 0 ?
                 gs_note_error(gs_error_VMerror) : 0)) < 0 ||
        (code = fn_common_scale((gs_function_t *)psfn,
                                (const gs_function_t *)pfn,
                                pranges, mem)) < 0 ||
        (code = fn_scale_functions((gs_function_t ***)&psfn->params.Functions,
                                   pfn->params.Functions,
                                   pfn->params.n, pranges, false, mem)) < 0) {
        gs_function_free((gs_function_t *)psfn, true, mem);
        return code;
    }
    *ppsfn = psfn;
    return 0;
}
