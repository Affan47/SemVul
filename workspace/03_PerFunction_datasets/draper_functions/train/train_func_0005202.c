compute_incr(pwl_susp_type susp, long *n, long cur)
{
    double target;
    while (*n == 0) {
        *n = getfixnum(car(susp->bpt_ptr)) - cur;

        if (cdr(susp->bpt_ptr))
            target = getflonum(car(cdr(susp->bpt_ptr)));
        else target = 0.0;
        if (*n > 0) susp->incr = (target - susp->lvl) / *n;
        else if (compute_lvl(susp)) return true;
    }
    return false;
}
