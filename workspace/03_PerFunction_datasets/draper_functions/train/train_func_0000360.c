pdf_count_pages(const char *filename)
{
    char gscommand[CMDLINE_MAX];
    char output[31] = "";
    int pagecount;
    size_t bytes;

    snprintf(gscommand, CMDLINE_MAX, "%s -dNODISPLAY -q -c "
	     "'/pdffile (%s) (r) file def pdfdict begin pdffile pdfopen begin "
	     "(PageCount: ) print pdfpagecount == flush currentdict pdfclose "
	     "end end quit'",
	     gspath, filename);

    FILE *pd = popen(gscommand, "r");
    if (!pd)
      rip_die(EXIT_STARVED, "Failed to execute ghostscript to determine number of input pages!\n");

    bytes = fread(output, 1, 31, pd);
    pclose(pd);

    if (bytes <= 0 || sscanf(output, "PageCount: %d", &pagecount) < 1)
      pagecount = -1;

    return pagecount;
}
