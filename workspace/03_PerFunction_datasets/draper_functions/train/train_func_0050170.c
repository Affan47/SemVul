pixcmapReadStream(FILE  *fp)
{
l_int32   rval, gval, bval;
l_int32   i, index, ret, depth, ncolors;
PIXCMAP  *cmap;

    PROCNAME("pixcmapReadStream");

    if (!fp)
        return (PIXCMAP *)ERROR_PTR("stream not defined", procName, NULL);

    ret = fscanf(fp, "\nPixcmap: depth = %d bpp; %d colors\n",
                 &depth, &ncolors);
    if (ret != 2 ||
        (depth != 1 && depth != 2 && depth != 4 && depth != 8) ||
        (ncolors < 2 || ncolors > 256))
        return (PIXCMAP *)ERROR_PTR("invalid cmap size", procName, NULL);
    fscanf(fp, "Color    R-val    G-val    B-val\n");
    fscanf(fp, "--------------------------------\n");

    if ((cmap = pixcmapCreate(depth)) == NULL)
        return (PIXCMAP *)ERROR_PTR("cmap not made", procName, NULL);
    for (i = 0; i < ncolors; i++) {
        fscanf(fp, "%3d       %3d      %3d      %3d\n",
                &index, &rval, &gval, &bval);
        pixcmapAddColor(cmap, rval, gval, bval);
    }

    return cmap;
}
