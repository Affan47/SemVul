bzfile_fill_inbuf(struct bzfile *fil)
{
    avssize_t res;
    avoff_t inoff = bz_total_in(fil->s);

    res = av_pread(fil->infile, fil->inbuf, INBUFSIZE, inoff);
    if(res < 0)
        return res;

    fil->s->next_in = fil->inbuf;
    fil->s->avail_in = res;

    return 0;
}
