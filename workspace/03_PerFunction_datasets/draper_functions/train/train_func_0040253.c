_dxf_getHwGatherFlags(gatherO go, int *flags)
{
    gatherP gop;

    if (! go)
	return ERROR;

    gop = _getHwGatherData(go);

    if (!gop)
	return ERROR;

    if (flags)
        *flags = gop->flags;

    return OK;
}
