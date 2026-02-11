gs_setlinecap(gs_state * pgs, gs_line_cap cap)
{
    if ((uint) cap > gs_line_cap_max)
        return_error(gs_error_rangecheck);
    pgs_lp->start_cap = cap;
    pgs_lp->end_cap   = cap;
    pgs_lp->dash_cap  = cap;
    return 0;
}
