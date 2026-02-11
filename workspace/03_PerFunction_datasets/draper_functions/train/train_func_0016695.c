_mpd_get_rnd(const mpd_uint_t *data, mpd_ssize_t len, int use_msd)
{
    mpd_uint_t rnd = 0, rest = 0, word;

    word = data[len-1];

    if (use_msd) {
        _mpd_divmod_pow10(&rnd, &rest, word, mpd_word_digits(word)-1);
        if (len > 1 && rest == 0) {
             rest = !_mpd_isallzero(data, len-1);
        }
    }
    else {
        rest = !_mpd_isallzero(data, len);
    }

    return (rnd == 0 || rnd == 5) ? rnd + !!rest : rnd;
}
