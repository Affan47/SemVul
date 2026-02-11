setTarget(MaState *state, cchar *name, cchar *details)
{
    if (httpSetRouteTarget(state->route, name, details) < 0) {
        mprError("Bad \"%s\" directive at line %d in %s\nLine: %s %s %s\n",
                state->key, state->lineNumber, state->filename, state->key, name, details);
        return MPR_ERR_BAD_SYNTAX;
    }
    return 0;
}
