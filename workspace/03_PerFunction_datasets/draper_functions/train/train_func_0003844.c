coeff_to_string(char *s, const mpd_t *dec)
{
    mpd_uint_t x;
    mpd_ssize_t i;


    x = mpd_msword(dec);
    s = word_to_string(s, x, mpd_word_digits(x), NULL);


    for (i=dec->len-2; i >= 0; --i) {
        x = dec->data[i];
        s = word_to_string(s, x, MPD_RDIGITS, NULL);
    }

    return s;
}
