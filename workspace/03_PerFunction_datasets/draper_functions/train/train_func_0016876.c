cos_stream_write(const cos_object_t *pco, gx_device_pdf *pdev, gs_id object_id)
{
    stream *s = pdev->strm;
    const cos_stream_t *const pcs = (const cos_stream_t *)pco;
    int code;

    if (pcs->input_strm != NULL) {
        stream *s = pco->input_strm;
        int status = s_close_filters(&s, NULL);

        if (status < 0)
            return_error(gs_error_ioerror);

        ((cos_object_t *)pco)->input_strm = 0;
    }
    stream_puts(s, "<<");
    cos_elements_write(s, pcs->elements, pdev, false, object_id);
    pprintld1(s, "/Length %ld>>stream\n", cos_stream_length(pcs));
    code = cos_stream_contents_write(pcs, pdev);
    stream_puts(s, "\nendstream\n");

    return code;
}
