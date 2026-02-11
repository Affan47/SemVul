jk_sb_flush(jk_sockbuf_t *sb)
{
    if (sb) {
        int save_out = sb->end;
        sb->end = sb->start = 0;
        if (save_out) {
            return send(sb->sd, sb->buf, save_out, 0) == save_out;
        }
        return JK_TRUE;
    }

    return JK_FALSE;
}
