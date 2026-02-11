pixcmapAddRGBA(PIXCMAP  *cmap,
               l_int32   rval,
               l_int32   gval,
               l_int32   bval,
               l_int32   aval)
{
RGBA_QUAD  *cta;

    PROCNAME("pixcmapAddRGBA");

    if (!cmap)
        return ERROR_INT("cmap not defined", procName, 1);
    if (cmap->n >= cmap->nalloc)
        return ERROR_INT("no free color entries", procName, 1);

    cta = (RGBA_QUAD *)cmap->array;
    cta[cmap->n].red = rval;
    cta[cmap->n].green = gval;
    cta[cmap->n].blue = bval;
    cta[cmap->n].alpha = aval;
    cmap->n++;
    return 0;
}
