deflate_flusher(ScmPort *port, int cnt, int forcep)
{
    ScmZlibInfo *info = SCM_PORT_ZLIB_INFO(port);
    z_streamp strm = SCM_PORT_ZSTREAM(port);
    int ret, nread, nwrite, total = 0;
    unsigned char *inbuf = (unsigned char*)port->src.buf.buffer;
    unsigned char outbuf[CHUNK];

    strm->next_in = inbuf;
    strm->avail_in = SCM_PORT_BUFFER_AVAIL(port);

    if (info->flush == Z_NO_FLUSH && forcep) {
        info->flush = Z_SYNC_FLUSH;
    }

    for (;;) {
        strm->next_out = outbuf;
        strm->avail_out = CHUNK;
        ret = deflate(strm, info->flush);
        SCM_ASSERT(ret == Z_OK);
        if (strm->avail_out != 0) {
            info->flush = Z_NO_FLUSH;
        }
        nread = strm->next_in - inbuf;
        nwrite = strm->next_out - outbuf;
        total += nread;
        if (nwrite > 0) {
            Scm_Putz((char*)outbuf, nwrite, info->remote);
        }
        if (forcep && (total < cnt)) {
            continue;
        }
        return total;
    }
}
