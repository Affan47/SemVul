fpixReadStream(FILE  *fp)
{
l_int32     w, h, nbytes, version;
l_float32  *data;
FPIX       *fpix;

    PROCNAME("fpixReadStream");

    if (!fp)
        return (FPIX *)ERROR_PTR("stream not defined", procName, NULL);

    if (fscanf(fp, "\nFPix Version %d\n", &version) != 1)
        return (FPIX *)ERROR_PTR("not a fpix file", procName, NULL);
    if (version != FPIX_VERSION_NUMBER)
        return (FPIX *)ERROR_PTR("invalid fpix version", procName, NULL);
    if (fscanf(fp, "w = %d, h = %d, nbytes = %d\n", &w, &h, &nbytes) != 3)
        return (FPIX *)ERROR_PTR("read fail for data size", procName, NULL);

    if ((fpix = fpixCreate(w, h)) == NULL)
        return (FPIX *)ERROR_PTR("fpix not made", procName, NULL);
    data = fpixGetData(fpix);
    if (fread(data, 1, nbytes, fp) != nbytes)
        return (FPIX *)ERROR_PTR("read error for nbytes", procName, NULL);


    fpixEndianByteSwap(fpix, fpix);
    return fpix;
}
