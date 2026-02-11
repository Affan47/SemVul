fpixPrintStream(FILE    *fp,
                FPIX    *fpix,
                l_int32  factor)
{
l_int32    i, j, w, h, count;
l_float32  val;

    PROCNAME("fpixPrintStream");

    if (!fp)
        return ERROR_INT("stream not defined", procName, 1);
    if (!fpix)
        return ERROR_INT("fpix not defined", procName, 1);
    if (factor < 1)
        return ERROR_INT("sampling factor < 1f", procName, 1);

    fpixGetDimensions(fpix, &w, &h);
    fprintf(fp, "\nFPix: w = %d, h = %d\n", w, h);
    for (i = 0; i < h; i += factor) {
        for (count = 0, j = 0; j < w; j += factor, count++) {
            fpixGetPixel(fpix, j, i, &val);
            fprintf(fp, "val[%d, %d] = %f   ", i, j, val);
            if ((count + 1) % 3 == 0) fprintf(fp, "\n");
        }
        if (count % 3) fprintf(fp, "\n");
     }
     fprintf(fp, "\n");
     return 0;
}
