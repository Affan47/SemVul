_mpd_cmp(const mpd_t *a, const mpd_t *b)
{
    mpd_ssize_t adjexp_a, adjexp_b;


    if (a == b) {
        return 0;
    }


    if (mpd_isinfinite(a)) {
        if (mpd_isinfinite(b)) {
            return mpd_isnegative(b) - mpd_isnegative(a);
        }
        return mpd_arith_sign(a);
    }
    if (mpd_isinfinite(b)) {
        return -mpd_arith_sign(b);
    }


    if (mpd_iszerocoeff(a)) {
        if (mpd_iszerocoeff(b)) {
            return 0;
        }
        return -mpd_arith_sign(b);
    }
    if (mpd_iszerocoeff(b)) {
        return mpd_arith_sign(a);
    }


    if (mpd_sign(a) != mpd_sign(b)) {
        return mpd_sign(b) - mpd_sign(a);
    }


    adjexp_a = mpd_adjexp(a);
    adjexp_b = mpd_adjexp(b);
    if (adjexp_a != adjexp_b) {
        if (adjexp_a < adjexp_b) {
            return -1 * mpd_arith_sign(a);
        }
        return mpd_arith_sign(a);
    }


    return _mpd_cmp_same_adjexp(a, b) * mpd_arith_sign(a);
}
