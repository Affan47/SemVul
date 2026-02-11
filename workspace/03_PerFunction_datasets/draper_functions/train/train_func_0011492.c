mpd_qcopy_sign(mpd_t *result, const mpd_t *a, const mpd_t *b, uint32_t *status)
{
    uint8_t sign_b = mpd_sign(b);

    if (!mpd_qcopy(result, a, status)) {
        return 0;
    }
    mpd_set_sign(result, sign_b);
    return 1;
}
