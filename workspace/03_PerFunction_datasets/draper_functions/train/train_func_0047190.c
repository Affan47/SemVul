mpd_setdigits(mpd_t *result)
{
    mpd_ssize_t wdigits = mpd_word_digits(mpd_msword(result));
    result->digits = wdigits + (result->len-1) * MPD_RDIGITS;
}
