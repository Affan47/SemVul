pixVShearCenter(PIX       *pixd,
                PIX       *pixs,
                l_float32  radang,
                l_int32    incolor)
{
    PROCNAME("pixVShearCenter");

    if (!pixs)
        return (PIX *)ERROR_PTR("pixs not defined", procName, pixd);

    return pixVShear(pixd, pixs, pixGetWidth(pixs) / 2, radang, incolor);
}
