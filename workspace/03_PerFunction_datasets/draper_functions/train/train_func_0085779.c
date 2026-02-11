bz_new_stream(bz_stream **resp)
{
    int res;
    bz_stream *s;

    AV_NEW(s);
    memset(s, 0, sizeof(*s));
    res = BZ2_bzDecompressInit(s, 0, 0);
    if(res != BZ_OK) {
        *resp = NULL;
        av_log(AVLOG_ERROR, "BZFILE: decompress init error: %i", res);
        return -EIO;
    }

    *resp = s;
    return 0;
}
