gz_error(state, err, msg)
    gz_statep state;
    int err;
    const char *msg;
{

    if (state->msg != NULL) {
        if (state->err != Z_MEM_ERROR)
            free(state->msg);
        state->msg = NULL;
    }


    if (err != Z_OK && err != Z_BUF_ERROR)
        state->x.have = 0;


    state->err = err;
    if (msg == NULL)
        return;


    if (err == Z_MEM_ERROR)
        return;


    if ((state->msg = (char *)malloc(strlen(state->path) + strlen(msg) + 3)) ==
            NULL) {
        state->err = Z_MEM_ERROR;
        return;
    }
#if !defined(NO_snprintf) && !defined(NO_vsnprintf)
    snprintf(state->msg, strlen(state->path) + strlen(msg) + 3,
             "%s%s%s", state->path, ": ", msg);
#else
    strcpy(state->msg, state->path);
    strcat(state->msg, ": ");
    strcat(state->msg, msg);
#endif
    return;
}
