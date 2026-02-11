convertG4ToPSString(const char  *filein,
                    char       **poutstr,
                    l_int32     *pnbytes,
                    l_int32      x,
                    l_int32      y,
                    l_int32      res,
                    l_float32    scale,
                    l_int32      pageno,
                    l_int32      maskflag,
                    l_int32      endpage)
{
char         *outstr;
l_float32     xpt, ypt, wpt, hpt;
L_COMP_DATA  *cid;

    PROCNAME("convertG4ToPSString");

    if (!poutstr)
        return ERROR_INT("&outstr not defined", procName, 1);
    if (!pnbytes)
        return ERROR_INT("&nbytes not defined", procName, 1);
    *poutstr = NULL;
    *pnbytes = 0;
    if (!filein)
        return ERROR_INT("filein not defined", procName, 1);

    if ((cid = l_generateG4Data(filein, 1)) == NULL)
        return ERROR_INT("g4 data not made", procName, 1);


    if (scale == 0.0)
        scale = 1.0;
    if (res <= 0) {
        if (cid->res > 0) {
            res = cid->res;
        } else {
            if (cid->h <= 3509)
                res = 300;
            else
                res = 600;
        }
    }
    xpt = scale * x * 72. / res;
    ypt = scale * y * 72. / res;
    wpt = scale * cid->w * 72. / res;
    hpt = scale * cid->h * 72. / res;

    if (pageno == 0)
        pageno = 1;

#if  DEBUG_G4
    fprintf(stderr, "w = %d, h = %d, minisblack = %d\n",
            cid->w, cid->h, cid->minisblack);
    fprintf(stderr, "comp bytes = %ld, nbytes85 = %ld\n",
            (unsigned long)cid->nbytescomp, (unsigned long)cid->nbytes85);
    fprintf(stderr, "xpt = %7.2f, ypt = %7.2f, wpt = %7.2f, hpt = %7.2f\n",
             xpt, ypt, wpt, hpt);
#endif


    outstr = generateG4PS(filein, cid, xpt, ypt, wpt, hpt,
                          maskflag, pageno, endpage);
    if (!outstr)
        return ERROR_INT("outstr not made", procName, 1);
    *poutstr = outstr;
    *pnbytes = strlen(outstr);
    l_compdataDestroy(&cid);
    return 0;
}
