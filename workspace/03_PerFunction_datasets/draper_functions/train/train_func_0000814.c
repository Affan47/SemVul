pdfwrite_pdf_open_document(gx_device_pdf * pdev)
{
    if (!is_in_page(pdev) && pdf_stell(pdev) == 0) {
        stream *s = pdev->strm;
        int level = (int)(pdev->CompatibilityLevel * 10 + 0.5);

        pdev->binary_ok = !pdev->params.ASCII85EncodePages;
        if (pdev->ForOPDFRead) {
            int code, status;
            char BBox[256];
            int width = (int)(pdev->width * 72.0 / pdev->HWResolution[0] + 0.5);
            int height = (int)(pdev->height * 72.0 / pdev->HWResolution[1] + 0.5);

            if (pdev->ProduceDSC)
                pdev->CompressEntireFile = 0;
            else {
                stream_write(s, (byte *)"%!\r", 3);
                gs_sprintf(BBox, "%%%%BoundingBox: 0 0 %d %d\n", width, height);
                stream_write(s, (byte *)BBox, strlen(BBox));
                if (pdev->params.CompressPages || pdev->CompressEntireFile) {


                    stream_write(s, (byte *)"currentfile /ASCII85Decode filter /LZWDecode filter cvx exec\n", 61);
                    code = encode(&s, &s_A85E_template, pdev->pdf_memory);
                    if (code < 0)
                        return code;
                    code = encode(&s, &s_LZWE_template, pdev->pdf_memory);
                    if (code < 0)
                        return code;
                }
                stream_puts(s, "/DSC_OPDFREAD false def\n");
                code = copy_procsets(s, pdev->HaveTrueTypes, true);
                if (code < 0)
                    return code;
                if (!pdev->CompressEntireFile) {
                    status = s_close_filters(&s, pdev->strm);
                    if (status < 0)
                        return_error(gs_error_ioerror);
                } else
                    pdev->strm = s;
                if(pdev->SetPageSize)
                    stream_puts(s, "/SetPageSize true def\n");
                if(pdev->RotatePages)
                    stream_puts(s, "/RotatePages true def\n");
                if(pdev->FitPages)
                    stream_puts(s, "/FitPages true def\n");
                if(pdev->CenterPages)
                    stream_puts(s, "/CenterPages true def\n");
                pdev->OPDFRead_procset_length = stell(s);
            }
        }
        if (!(pdev->ForOPDFRead)) {
            pprintd2(s, "%%PDF-%d.%d\n", level / 10, level % 10);
            if (pdev->binary_ok)
                stream_puts(s, "%\307\354\217\242\n");
        }
    }


    if (!pdev->params.CompressPages)
        pdev->compression = pdf_compress_none;
    else
        pdev->compression = pdf_compress_Flate;
    return 0;
}
