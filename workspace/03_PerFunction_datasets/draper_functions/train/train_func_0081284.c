addLanguageSuffixDirective(MaState *state, cchar *key, cchar *value)
{
    char    *lang, *ext, *position;
    int     flags;

    if (!maTokenize(state, value, "%S %S ?S", &lang, &ext, &position)) {
        return MPR_ERR_BAD_SYNTAX;
    }
    flags = 0;
    if (scasematch(position, "after")) {
        flags |= HTTP_LANG_AFTER;
    } else if (scasematch(position, "before")) {
        flags |= HTTP_LANG_BEFORE;
    }
    httpAddRouteLanguageSuffix(state->route, lang, ext, flags);
    return 0;
}
