mpd_qfinalize(mpd_t *result, const mpd_context_t *ctx, uint32_t *status)
{
    if (mpd_isspecial(result)) {
        if (mpd_isnan(result)) {
            _mpd_fix_nan(result, ctx);
        }
        return;
    }

    _mpd_check_exp(result, ctx, status);
    _mpd_check_round(result, ctx, status);
}
