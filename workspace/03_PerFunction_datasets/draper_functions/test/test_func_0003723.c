regTestWritePixAndCheck(L_REGPARAMS  *rp,
                        PIX          *pix,
                        l_int32       format)
{
char   namebuf[256];

    PROCNAME("regTestWritePixAndCheck");

    if (!rp)
        return ERROR_INT("rp not defined", procName, 1);
    if (!pix) {
        rp->success = FALSE;
        return ERROR_INT("pix not defined", procName, 1);
    }
    if (format < 0 || format >= NumImageFileFormatExtensions) {
        rp->success = FALSE;
        return ERROR_INT("invalid format", procName, 1);
    }


    snprintf(namebuf, sizeof(namebuf), "/tmp/%s.%d.%s", rp->testname,
             rp->index + 1, ImageFileFormatExtensions[format]);


    pixWrite(namebuf, pix, format);


    regTestCheckFile(rp, namebuf);

    return 0;
}
