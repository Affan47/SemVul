lineartfake_proc_data(Microtek2_Scanner *ms)
{
    Microtek2_Device *md;
    Microtek2_Info *mi;
    SANE_Status status;
    uint8_t *from;
    int right_to_left;


    DBG(30, "lineartfake_proc_data: lines=%d, bpl=%d, ppl=%d, depth=%d\n",
             ms->src_lines_to_read, ms->bpl, ms->ppl, ms->depth);

    md = ms->dev;
    mi = &md->info[md->scan_source];
    right_to_left = mi->direction & MI_DATSEQ_RTOL;

    if ( right_to_left == 1 )
        from = ms->buf.src_buf + ms->ppl - 1;
    else
        from = ms->buf.src_buf;

    do
      {
        status = lineartfake_copy_pixels(ms,
                                         from,
                                         ms->ppl,
                                         ms->threshold,
                                         right_to_left,
                                         ms->fp);
        if ( status != SANE_STATUS_GOOD )
            return status;

        from += ms->bpl;
        --ms->src_lines_to_read;
      } while ( ms->src_lines_to_read > 0 );

    return SANE_STATUS_GOOD;
}
