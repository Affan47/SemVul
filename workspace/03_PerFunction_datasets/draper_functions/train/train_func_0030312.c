check_block_tolerance(const stream_stat& ss,
                      const double frac_tol,
                      const int abs_tol) {

    const int min(static_cast<int>(compat_round(ss.min())));
    if (check_block_single_tolerance(ss,min,abs_tol)) return true;
    const int ftol(static_cast<int>(std::floor(min * frac_tol)));
    if (ftol <= abs_tol) return false;
    return check_block_single_tolerance(ss, min, ftol);
}
