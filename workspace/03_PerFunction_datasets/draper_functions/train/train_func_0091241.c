fn_ElIn_is_monotonic(const gs_function_t * pfn_common,
                     const float *lower, const float *upper, uint *mask)
{
    const gs_function_ElIn_t *const pfn =
        (const gs_function_ElIn_t *)pfn_common;

    if (lower[0] > pfn->params.Domain[1] ||
        upper[0] < pfn->params.Domain[0]
        )
        return_error(gs_error_rangecheck);
    *mask = 0;
    return 1;
}
