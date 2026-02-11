gzclearerr (file)
    gzFile file;
{
    gz_stream *s = (gz_stream*)file;

    if (s == NULL) return;
    if (s->z_err != Z_STREAM_END) s->z_err = Z_OK;
    s->z_eof = 0;
    clearerr(s->file);
}
