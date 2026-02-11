pdf_scan_find_xref(PDFSCAN *ps)
{
    char buf[4096];
    int i, j;
    int code = -1;
    int count;
    pdf_scan_seek(ps, 0, PDFSEEK_END);
    count = min((int)sizeof(buf), ps->offset);
    pdf_scan_seek(ps, -count, PDFSEEK_CUR);
    count = (int)fread(buf, 1, sizeof(buf), ps->file);
    pdf_scan_seek(ps, 0, PDFSEEK_SET);
    if (count == 0)
	return -1;
    i = count - 5;
    while (i > 0) {

	if (memcmp(buf+i, "%%EOF", 5) == 0) {
	    code = 0;
	    break;
	}
	i--;
    }
    if (i == 0) {
	pdf_scan_msgf(ps, "Failed to find %%EOF\n");
	code = -1;
    }
    if (code == 0) {

	j = previous_line(buf, i);
	if (j >= 0)
	    ps->xref_offset = atol(buf+j);
	else
	    code = -1;
	i = j;
	if (ps->xref_offset == 0)
	    code = -1;
	if (code != 0)
	    pdf_scan_msgf(ps, "Failed to find cross reference table\n");
    }

    if (code == 0) {

	j = previous_line(buf, i);
	if (j >= 0) {
	    if (memcmp(buf+j, "startxref", 9) != 0)
		code = -1;
	}
	else {
	    code = -1;
	}
	if (code != 0)
	    pdf_scan_msgf(ps, "Failed to find startxref\n");
    }
    return code;
}
