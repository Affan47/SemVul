stream_to_none(gx_device_pdf * pdev)
{
    stream *s = pdev->strm;
    gs_offset_t length;
    int code;

    if (pdev->ResourcesBeforeUsage) {
        int code = pdf_exit_substream(pdev);

        if (code < 0)
            return code;
    } else {
        if (pdev->vgstack_depth) {
            code = pdf_restore_viewer_state(pdev, s);
            if (code < 0)
                return code;
        }
        if (pdev->compression_at_page_start == pdf_compress_Flate) {
            stream *fs = s->strm;

            if (!pdev->binary_ok) {
                sclose(s);
                gs_free_object(pdev->pdf_memory, s->cbuf, "A85E contents buffer");
                gs_free_object(pdev->pdf_memory, s, "A85E contents stream");
                pdev->strm = s = fs;
                fs = s->strm;
            }
            sclose(s);
            gs_free_object(pdev->pdf_memory, s->cbuf, "zlib buffer");
            gs_free_object(pdev->pdf_memory, s, "zlib stream");
            pdev->strm = fs;
        }
        pdf_end_encrypt(pdev);
        s = pdev->strm;
        length = pdf_stell(pdev) - pdev->contents_pos;
        if (pdev->PDFA != 0)
            stream_puts(s, "\n");
        stream_puts(s, "endstream\n");
        pdf_end_obj(pdev, resourceStream);
        pdf_open_obj(pdev, pdev->contents_length_id, resourceLength);
        pprintld1(s, "%ld\n", (long)length);
        pdf_end_obj(pdev, resourceLength);
    }
    return PDF_IN_NONE;
}
