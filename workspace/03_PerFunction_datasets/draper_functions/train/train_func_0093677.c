pixReadMemJpeg(const l_uint8  *cdata,
               size_t          size,
               l_int32         cmflag,
               l_int32         reduction,
               l_int32        *pnwarn,
               l_int32         hint)
{
l_int32   ret;
l_uint8  *comment;
FILE     *fp;
PIX      *pix;

    PROCNAME("pixReadMemJpeg");

    if (!cdata)
        return (PIX *)ERROR_PTR("cdata not defined", procName, NULL);

#if HAVE_FMEMOPEN
    if ((fp = fmemopen((l_uint8 *)cdata, size, "r")) == NULL)
        return (PIX *)ERROR_PTR("stream not opened", procName, NULL);
#else
    L_WARNING("work-around: writing to a temp file\n", procName);
    fp = tmpfile();
    fwrite(cdata, 1, size, fp);
    rewind(fp);
#endif
    pix = pixReadStreamJpeg(fp, cmflag, reduction, pnwarn, hint);
    if (pix) {
        ret = fgetJpegComment(fp, &comment);
        if (!ret && comment) {
            pixSetText(pix, (char *)comment);
            FREE(comment);
        }
    }
    fclose(fp);
    if (!pix) L_ERROR("pix not read\n", procName);
    return pix;
}
