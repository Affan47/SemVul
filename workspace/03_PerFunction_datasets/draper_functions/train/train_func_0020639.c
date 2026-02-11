gs_jpeg_create_decompress(stream_DCT_state * st)
{
    gs_jpeg_error_setup(st);

    if (setjmp(find_jmp_buf(st->data.common->exit_jmpbuf)))
        return_error(gs_jpeg_log_error(st));

    jpeg_stream_data_common_init(st->data.decompress);
    jpeg_create_decompress(&st->data.decompress->dinfo);
    return 0;
}
