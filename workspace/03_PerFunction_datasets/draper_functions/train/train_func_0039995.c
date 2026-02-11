pixAddBorder(PIX      *pixs,
             l_int32   npix,
             l_uint32  val)
{
    PROCNAME("pixAddBorder");

    if (!pixs)
        return (PIX *)ERROR_PTR("pixs not defined", procName, NULL);
    if (npix == 0)
        return pixClone(pixs);
    return pixAddBorderGeneral(pixs, npix, npix, npix, npix, val);
}
