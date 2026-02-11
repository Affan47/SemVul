jk_sb_write(jk_sockbuf_t *sb, const void *buf, unsigned sz)
{
    if (sb && buf && sz) {
        if ((SOCKBUF_SIZE - sb->end) >= sz) {
            memcpy(sb->buf + sb->end, buf, sz);
            sb->end += sz;
        }
        else {
            if (!jk_sb_flush(sb)) {
                return JK_FALSE;
            }
            if (sz > SOCKBUF_SIZE) {
                return (send(sb->sd, (char *)buf, sz, 0) == (int)sz);
            }

            memcpy(sb->buf + sb->end, buf, sz);
            sb->end += sz;
        }

        return JK_TRUE;
    }

    return JK_FALSE;
}
