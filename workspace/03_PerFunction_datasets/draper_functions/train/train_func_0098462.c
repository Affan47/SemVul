pdf_end_encrypt(gx_device_pdf * pdev)
{
    if (pdev->KeyLength) {
        stream *s = pdev->strm;
        stream *fs = s->strm;

        sclose(s);
        gs_free_object(pdev->pdf_memory, s->cbuf, "encrypt buffer");
        gs_free_object(pdev->pdf_memory, s, "encrypt stream");
        pdev->strm = fs;
    }
}
