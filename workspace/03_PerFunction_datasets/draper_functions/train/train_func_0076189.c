pixDeserializeFromMemory(const l_uint32  *data,
                         size_t           nbytes)
{
char      *id;
l_int32    w, h, d, wpl, imdatasize, cdatasize, ncolors;
l_uint32  *imdata;
PIX       *pixd;
PIXCMAP   *cmap;

    PROCNAME("pixDeserializeFromMemory");

    if (!data)
        return (PIX *)ERROR_PTR("data not defined", procName, NULL);
    if (nbytes < 32)
        return (PIX *)ERROR_PTR("invalid data", procName, NULL);

    id = (char *)data;
    if (id[0] != 's' || id[1] != 'p' || id[2] != 'i' || id[3] != 'x')
        return (PIX *)ERROR_PTR("invalid id string", procName, NULL);
    w = data[1];
    h = data[2];
    d = data[3];
    if ((pixd = pixCreate(w, h, d)) == NULL)
        return (PIX *)ERROR_PTR("pix not made", procName, NULL);

    wpl = data[4];
    ncolors = data[5];
    if ((cdatasize = data[6]) > 0) {
        cmap = pixcmapDeserializeFromMemory((l_uint8 *)(&data[7]), ncolors,
                                            cdatasize);
        if (!cmap)
            return (PIX *)ERROR_PTR("cmap not made", procName, NULL);
        pixSetColormap(pixd, cmap);
    }

    imdata = pixGetData(pixd);
    imdatasize = nbytes - 32 - cdatasize;
    memcpy((char *)imdata, (char *)(data + 8 + cdatasize / 4), imdatasize);

#if  DEBUG_SERIALIZE
    fprintf(stderr, "Deserialize: "
            "raster size = %d, ncolors in cmap = %d, total bytes = %d\n",
            imdatasize, ncolors, nbytes);
#endif

    return pixd;
}
