dewarpWriteStream(FILE      *fp,
                  L_DEWARP  *dew)
{
l_int32  hdispar;

    PROCNAME("dewarpWriteStream");

    if (!fp)
        return ERROR_INT("stream not defined", procName, 1);
    if (!dew)
        return ERROR_INT("dew not defined", procName, 1);

    fprintf(fp, "\nDewarp Version %d\n", DEWARP_VERSION_NUMBER);
    fprintf(fp, "pageno = %d, sampling = %d\n", dew->pageno, dew->sampling);
    hdispar = (dew->samphdispar) ? 1 : 0;
    fprintf(fp, "nx = %d, ny = %d, horiz_disparity = %d\n",
            dew->nx, dew->ny, hdispar);

    fpixWriteStream(fp, dew->sampvdispar);
    if (hdispar)
        fpixWriteStream(fp, dew->samphdispar);

    return 0;
}
