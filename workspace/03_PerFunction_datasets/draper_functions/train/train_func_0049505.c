get_fileconverter_handle(const char *alreadyread, FILE **fd, pid_t *pid)
{
    pid_t kid1;
    FILE *kid1out;
    const char *pagesize;
    char *fileconv;
    kid1_userdata_t kid1_userdata;

    _log("\nStarting converter for non-PostScript files\n");

    if (isempty(fileconverter) && !guess_fileconverter())
        rip_die(EXIT_PRNERR_NORETRY_BAD_SETTINGS, "Cannot convert file to "
                "Postscript (missing fileconverter).");


    pagesize = option_get_value(find_option("PageSize"), optionset("header"));
    if (pagesize && startswith(fileconverter, "a2ps")) {
        if (!strcasecmp(pagesize, "letter"))
            pagesize = "Letterdj";
        else if (!strcasecmp(pagesize, "a4"))
            pagesize = "A4dj";
    }

    if (do_docs)
        snprintf(get_current_job()->title, 128, "Documentation for the %s", printer_model);

    fileconv = fileconverter_from_template(fileconverter, pagesize, get_current_job()->title);

    kid1_userdata.fileconv = fileconv;
    kid1_userdata.alreadyread = alreadyread;
    kid1 = start_process("kid1", exec_kid1, &kid1_userdata, NULL, &kid1out);
    if (kid1 < 0)
        rip_die(EXIT_PRNERR_NORETRY_BAD_SETTINGS, "Cannot convert file to "
                "Postscript (Cannot fork for kid1!)\n");

    *fd = kid1out;
    *pid = kid1;

    free(fileconv);
}
