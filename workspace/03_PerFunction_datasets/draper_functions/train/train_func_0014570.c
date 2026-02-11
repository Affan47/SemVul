convertToPdfSegmented(const char  *filein,
                      l_int32      res,
                      l_int32      type,
                      l_int32      thresh,
                      BOXA        *boxa,
                      l_int32      quality,
                      l_float32    scalefactor,
                      const char  *fileout)
{
l_int32  ret;
PIX     *pixs;

    PROCNAME("convertToPdfSegmented");

    if (!filein)
        return ERROR_INT("filein not defined", procName, 1);
    if (!fileout)
        return ERROR_INT("fileout not defined", procName, 1);
    if (type != L_G4_ENCODE && type != L_JPEG_ENCODE &&
        type != L_FLATE_ENCODE)
        return ERROR_INT("invalid conversion type", procName, 1);
    if (boxa && scalefactor > 1.0) {
        L_WARNING("setting scalefactor to 1.0", procName);
        scalefactor = 1.0;
    }

    if ((pixs = pixRead(filein)) == NULL)
        return ERROR_INT("pixs not made", procName, 1);

    ret = pixConvertToPdfSegmented(pixs, res, type, thresh, boxa, quality,
                                   scalefactor, fileout, filein);
    pixDestroy(&pixs);
    return ret;
}
