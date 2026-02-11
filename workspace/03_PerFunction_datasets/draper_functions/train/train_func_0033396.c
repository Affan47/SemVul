write_xref_section(gx_device_pdf *pdev, FILE *tfile, int64_t start, int end, gs_offset_t resource_pos, gs_offset_t *Offsets)
{
    int64_t start_offset = (start - pdev->FirstObjectNumber) * sizeof(gs_offset_t);

    gp_fseek_64(tfile, start_offset, SEEK_SET);
    {
        long i, r;

        for (i = start; i < end; ++i) {
            gs_offset_t pos;
            char str[21];

            r = fread(&pos, sizeof(pos), 1, tfile);
            if (r != 1)
                return(gs_note_error(gs_error_ioerror));
            if (pos & ASIDES_BASE_POSITION)
                pos += resource_pos - ASIDES_BASE_POSITION;
            pos -= pdev->OPDFRead_procset_length;


            if (!pdev->Linearise) {
                gs_sprintf(str, "%010"PRId64" 00000 n \n", pos);
                stream_puts(pdev->strm, str);
            }
            if (Offsets)
                Offsets[i] = pos;
        }
    }
    return 0;
}
