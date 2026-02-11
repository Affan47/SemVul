c_overprint_equal(const gs_composite_t * pct0, const gs_composite_t * pct1)
{
    if (pct0->type == pct1->type) {
        const gs_overprint_params_t *    pparams0;
        const gs_overprint_params_t *    pparams1;

        pparams0 = &((const gs_overprint_t *)(pct0))->params;
        pparams1 = &((const gs_overprint_t *)(pct1))->params;
        if (!pparams0->retain_any_comps)
            return !pparams1->retain_any_comps;
        else if (pparams0->retain_spot_comps)
            return pparams1->retain_spot_comps;
        else
            return pparams0->drawn_comps == pparams1->drawn_comps;
    } else
        return false;
}
