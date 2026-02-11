mpd_qrescale_fmt(mpd_t *result, const mpd_t *a, mpd_ssize_t exp,
                 const mpd_context_t *ctx, uint32_t *status)
{
    if (exp > MPD_MAX_EMAX+1 || exp < MPD_MIN_ETINY-MPD_MAX_PREC) {
        mpd_seterror(result, MPD_Invalid_operation, status);
        return;
    }

    _mpd_qrescale(result, a, exp, ctx, status);
}
