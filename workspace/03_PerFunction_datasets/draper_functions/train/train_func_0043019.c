lcf_next(TokenStream *ts)
{
    int i = 0;
    Token *tk = TkFilt(ts)->sub_ts->next(TkFilt(ts)->sub_ts);
    if (tk == NULL) {
        return tk;
    }
    while (tk->text[i] != '\0') {
        tk->text[i] = tolower(tk->text[i]);
        i++;
    }
    return tk;
}
