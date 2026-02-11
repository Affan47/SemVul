mpd_qget_ssize(const mpd_t *a, uint32_t *status)
{
    mpd_uint_t u;
    int isneg;

    u = mpd_qabs_uint(a, status);
    if (*status&MPD_Invalid_operation) {
        return MPD_SSIZE_MAX;
    }

    isneg = mpd_isnegative(a);
    if (u <= MPD_SSIZE_MAX) {
        return isneg ? -((mpd_ssize_t)u) : (mpd_ssize_t)u;
    }
    else if (isneg && u+(MPD_SSIZE_MIN+MPD_SSIZE_MAX) == MPD_SSIZE_MAX) {
        return MPD_SSIZE_MIN;
    }

    *status |= MPD_Invalid_operation;
    return MPD_SSIZE_MAX;
}
