bcf_sweep_fwd(bcf_sweep_t *sw)
{
    if ( sw->direction==SW_BWD ) sw_seek(sw, SW_FWD);

    long pos = hts_utell(sw->file);

    bcf1_t *rec = &sw->rec[0];
    int ret = bcf_read1(sw->file, sw->hdr, rec);

    if ( ret!=0 )
    {
        sw->idx_done = 1;
        sw->fp->idx_build_otf = 0;
        sw_seek(sw, SW_BWD);
        return NULL;
    }

    if ( !sw->idx_done )
    {
        if ( !sw->nidx || pos - sw->idx[sw->nidx-1] > sw->block_size )
        {
            sw->nidx++;
            hts_expand(uint64_t, sw->nidx, sw->midx, sw->idx);
            sw->idx[sw->nidx-1] = pos;
        }
    }
    return rec;
}
