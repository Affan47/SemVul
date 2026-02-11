mb_legacy_std_get_alpha(TokenStream *ts, char *token)
{
    char *t = ts->t;
    wchar_t wchr;
    int i;
    mbstate_t state; ZEROSET(&state, mbstate_t);

    i = mb_next_char(&wchr, t, &state);

    while (wchr != 0 && iswalnum(wchr)) {
        t += i;
        i = mb_next_char(&wchr, t, &state);
    }

    i = (int)(t - ts->t);
    if (i > MAX_WORD_SIZE) {
        i = MAX_WORD_SIZE - 1;
    }
    memcpy(token, ts->t, i);
    return i;
}
