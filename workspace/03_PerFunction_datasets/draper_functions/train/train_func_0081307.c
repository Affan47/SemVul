gx_device_open_output_file(const gx_device * dev, char *fname,
                           bool binary, bool positionable, FILE ** pfile)
{
    gs_parsed_file_name_t parsed;
    const char *fmt;
    char pfname[gp_file_name_sizeof];
    int code = gx_parse_output_file_name(&parsed, &fmt, fname, strlen(fname),
                                         dev->memory);

    if (code < 0)
        return code;
    if (parsed.iodev && !strcmp(parsed.iodev->dname, "%stdout%")) {
        if (parsed.fname)
            return_error(gs_error_undefinedfilename);
        *pfile = dev->memory->gs_lib_ctx->fstdout;

        return gp_setmode_binary(*pfile, true);
    } else if (parsed.iodev && !strcmp(parsed.iodev->dname, "%pipe%")) {
        positionable = false;
    }
    if (fmt) {
        long count1 = dev->PageCount + 1;

        while (*fmt != 'l' && *fmt != '%')
            --fmt;
        if (*fmt == 'l')
            gs_sprintf(pfname, parsed.fname, count1);
        else
            gs_sprintf(pfname, parsed.fname, (int)count1);
    } else if (parsed.len && strchr(parsed.fname, '%'))
        gs_sprintf(pfname, parsed.fname);
    else
        pfname[0] = 0;
    if (pfname[0]) {
        parsed.fname = pfname;
        parsed.len = strlen(parsed.fname);
    }
    if (positionable || (parsed.iodev && parsed.iodev != iodev_default(dev->memory))) {
        char fmode[4];

        if (!parsed.fname)
            return_error(gs_error_undefinedfilename);
        strcpy(fmode, gp_fmode_wb);
        if (positionable)
            strcat(fmode, "+");
        code = parsed.iodev->procs.gp_fopen(parsed.iodev, parsed.fname, fmode,
                                         pfile, NULL, 0);
        if (code)
            emprintf1(dev->memory,
                      "**** Could not open the file %s .\n",
                      parsed.fname);
        return code;
    }
    *pfile = gp_open_printer(dev->memory, (pfname[0] ? pfname : fname), binary);
    if (*pfile)
        return 0;
    emprintf1(dev->memory,
              "**** Could not open the file %s .\n",
              (pfname[0] ? pfname : fname));
    return_error(gs_error_invalidfileaccess);
}
