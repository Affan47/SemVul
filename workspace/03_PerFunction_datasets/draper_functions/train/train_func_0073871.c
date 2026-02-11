inflate64End(strm)
z_stream64p strm;
{
    struct inflate_state FAR *state;
    if (strm == Z_NULL || strm->state == Z_NULL)
        return Z_STREAM_ERROR;
    state = (struct inflate_state FAR *)strm->state;
    if (state->window != Z_NULL) free(state->window);
    free(strm->state);
    strm->state = Z_NULL;
    Tracev((stderr, "inflate: end\n"));
    return Z_OK;
}
