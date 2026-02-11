mpd_qcompare(mpd_t *result, const mpd_t *a, const mpd_t *b,
             const mpd_context_t *ctx, uint32_t *status)
{
    int c;

    if (mpd_isspecial(a) || mpd_isspecial(b)) {
        if (mpd_qcheck_nans(result, a, b, ctx, status)) {
            return INT_MAX;
        }
    }

    c = _mpd_cmp(a, b);
    _settriple(result, (c < 0), (c != 0), 0);
    return c;
}
