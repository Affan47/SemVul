_close_m2ts(BD_STREAM *st)
{
    if (st->fp != NULL) {
        file_close(st->fp);
        st->fp = NULL;
    }

    m2ts_filter_close(&st->m2ts_filter);

    libbdplus_m2ts_close(&st->bdplus);


    memset(&st->uo_mask, 0, sizeof(st->uo_mask));
}
