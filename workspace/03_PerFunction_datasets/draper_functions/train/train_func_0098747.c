notifyPageSent(TIFF* tif, PageType pt)
{
    if (curreq)
	server.notifyPageSent(*curreq, TIFFFileName(tif), pt);
}
