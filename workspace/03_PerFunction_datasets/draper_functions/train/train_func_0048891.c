mb_wst_next(TokenStream *ts)
{
    int i;
    char *start;
    char *t = ts->t;
    wchar_t wchr;
    mbstate_t *state = &(MBTS(ts)->state);

    i = mb_next_char(&wchr, t, state);
    while (wchr != 0 && iswspace(wchr)) {
        t += i;
        i = mb_next_char(&wchr, t, state);
    }
    if (wchr == 0) {
        return NULL;
    }

    start = t;
    t += i;
    i = mb_next_char(&wchr, t, state);
    while (wchr != 0 && !iswspace(wchr)) {
        t += i;
        i = mb_next_char(&wchr, t, state);
    }
    ts->t = t;
    return tk_set_ts(&(CTS(ts)->token), start, t, ts->text, 1);
}
