loadModuleDirective(MaState *state, cchar *key, cchar *value)
{
    char    *name, *path;

    if (!maTokenize(state, value, "%S %S", &name, &path)) {
        return MPR_ERR_BAD_SYNTAX;
    }
    if (maLoadModule(state->appweb, name, path) < 0) {

        return MPR_ERR_CANT_CREATE;
    }
    return 0;
}
