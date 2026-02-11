s_MD5C_get_digest(stream *s, byte *buf, int buf_length)
{
    stream_MD5E_state *const ss = (stream_MD5E_state *)s->state;
    gs_md5_state_t md5;
    byte b[16], *p;
    int l = min(16, buf_length), k;

    if (s->procs.process != s_MD5C_process)
        return 0;
    md5 = ss->md5;
    gs_md5_finish(&md5, b);
    memcpy(buf, b, l);
    for (p = b + l; p < b + sizeof(b); p += l) {
        for (k = 0; k < l && p + k < b + sizeof(b); k++)
            buf[k] ^= p[k];
    }
    return l;
}
