psdf_begin_binary(gx_device_psdf * pdev, psdf_binary_writer * pbw)
{
    gs_memory_t *mem = pbw->memory = pdev->v_memory;

    pbw->target = pdev->strm;
    pbw->dev = pdev;
    pbw->strm = 0;

    if (!pdev->binary_ok) {
#define BUF_SIZE 100
        byte *buf = gs_alloc_bytes(mem, BUF_SIZE, "psdf_begin_binary(buf)");
        stream_A85E_state *ss = (stream_A85E_state *)
            s_alloc_state(mem, s_A85E_template.stype,
                          "psdf_begin_binary(stream_state)");
        stream *s = s_alloc(mem, "psdf_begin_binary(stream)");

        if (buf == 0 || ss == 0 || s == 0) {
            gs_free_object(mem, s, "psdf_begin_binary(stream)");
            gs_free_object(mem, ss, "psdf_begin_binary(stream_state)");
            gs_free_object(mem, buf, "psdf_begin_binary(buf)");
            return_error(gs_error_VMerror);
        }
        ss->templat = &s_A85E_template;
        s_init_filter(s, (stream_state *)ss, buf, BUF_SIZE, pdev->strm);
#undef BUF_SIZE
        pbw->strm = s;
    } else {
        pbw->strm = pdev->strm;
    }
    return 0;
}
