pathx_error(struct pathx *path, const char **txt, int *pos) {
    int errcode = PATHX_ENOMEM;

    if (path != NULL) {
        if (path->state->errcode < ARRAY_CARDINALITY(errcodes))
            errcode = path->state->errcode;
        else
            errcode = PATHX_EINTERNAL;

        if (txt)
            *txt = path->state->txt;

        if (pos)
            *pos = path->state->pos - path->state->txt;
    }
    return errcodes[errcode];
}
