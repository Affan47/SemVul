zfile_compress_state(char *state, int statelen, char **resp)
{
    int res;
    z_stream s;
    int bufsize = sizeof(int) + statelen + statelen / 1000 + 1 + 12;
    char *cstate = av_malloc(bufsize);

    s.next_in = (Bytef*)state;
    s.avail_in = statelen;
    s.next_out = (Bytef*)( cstate + sizeof(int) );
    s.avail_out = bufsize - sizeof(int);
    s.zalloc = NULL;
    s.zfree = NULL;

    ((int *) cstate)[0] = statelen;

    res = deflateInit(&s, STATE_COMPRESS_LEVEL);
    if(res != Z_OK) {
        av_log(AVLOG_ERROR, "ZFILE: compress state failed");
        av_free(cstate);
        return -EIO;
    }

    res = deflate(&s, Z_FINISH);
    if(res != Z_STREAM_END) {
        av_log(AVLOG_ERROR, "ZFILE: compress state failed");
        av_free(cstate);
        return -EIO;
    }

    res = deflateEnd(&s);
    if(res != Z_OK) {
        av_log(AVLOG_ERROR, "ZFILE: compress state failed");
        av_free(cstate);
        return -EIO;
    }

    *resp = cstate;
    return sizeof(int) + s.total_out;
}
