s_init_filter(stream *fs, stream_state *fss, byte *buf, uint bsize,
              stream *target)
{
    const stream_template *templat = fss->templat;

    if (bsize < templat->min_in_size)
        return ERRC;
    s_std_init(fs, buf, bsize, &s_filter_write_procs, s_mode_write);
    fs->procs.process = templat->process;
    fs->state = fss;
    if (templat->init) {
        fs->end_status = (templat->init)(fss);
        if (fs->end_status < 0)
            return fs->end_status;
    }
    fs->strm = target;
    return 0;
}
