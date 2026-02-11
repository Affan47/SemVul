espLoadDirective(MaState *state, cchar *key, cchar *value)
{
    EspRoute    *eroute;
    char        *name, *path;

    if ((eroute = getEroute(state->route)) == 0) {
        return MPR_ERR_MEMORY;
    }
    if (!maTokenize(state, value, "%S %P", &name, &path)) {
        return MPR_ERR_BAD_SYNTAX;
    }
    eroute->appModuleName = sclone(name);
    eroute->appModulePath = sclone(path);
    return 0;
}
