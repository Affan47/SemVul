cmap_put_system_info(stream *s, const gs_cid_system_info_t *pcidsi)
{
    if (cid_system_info_is_null(pcidsi)) {
        stream_puts(s, " null ");
    } else {
        stream_puts(s, " 3 dict dup begin\n");
        stream_puts(s, "/Registry ");
        s_write_ps_string(s, pcidsi->Registry.data, pcidsi->Registry.size, 0);
        stream_puts(s, " def\n/Ordering ");
        s_write_ps_string(s, pcidsi->Ordering.data, pcidsi->Ordering.size, 0);
        pprintd1(s, " def\n/Supplement %d def\nend ", pcidsi->Supplement);
    }
}
