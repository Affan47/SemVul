gzprintf (gzFile file, const char *format, ...)
{
    int size, len;
    gz_statep state;
    z_streamp strm;
    va_list va;


    if (file == NULL)
        return -1;
    state = (gz_statep)file;
    strm = &(state->strm);


    if (state->mode != GZ_WRITE || state->err != Z_OK)
        return 0;


    if (state->size == 0 && gz_init(state) == -1)
        return 0;


    if (state->seek) {
        state->seek = 0;
        if (gz_zero(state, state->skip) == -1)
            return 0;
    }


    if (strm->avail_in && gz_comp(state, Z_NO_FLUSH) == -1)
        return 0;


    size = (int)(state->size);
    state->in[size - 1] = 0;
    va_start(va, format);
#ifdef NO_vsnprintf
#  ifdef HAS_vsprintf_void
    (void)vsprintf(state->in, format, va);
    va_end(va);
    for (len = 0; len < size; len++)
        if (state->in[len] == 0) break;
#  else
    len = vsprintf(state->in, format, va);
    va_end(va);
#  endif
#else
#  ifdef HAS_vsnprintf_void
    (void)vsnprintf(state->in, size, format, va);
    va_end(va);
    len = strlen(state->in);
#  else
    len = vsnprintf((char *)(state->in), size, format, va);
    va_end(va);
#  endif
#endif


    if (len <= 0 || len >= (int)size || state->in[size - 1] != 0)
        return 0;


    strm->avail_in = (unsigned)len;
    strm->next_in = state->in;
    state->pos += len;
    return len;
}
