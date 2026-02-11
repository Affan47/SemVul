xpmFreeInternAttrib(attrib)
    xpmInternAttrib *attrib;
{
    unsigned int a, ncolors;
    char **sptr;

    if (attrib->colorTable)
	xpmFreeColorTable(attrib->colorTable, attrib->ncolors);
    if (attrib->pixelindex)
	free(attrib->pixelindex);
    if (attrib->xcolors)
	free(attrib->xcolors);
    if (attrib->colorStrings) {
	ncolors = attrib->ncolors;
	for (a = 0, sptr = attrib->colorStrings; a < ncolors; a++, sptr++)
	    if (*sptr)
		free(*sptr);
	free(attrib->colorStrings);
    }
}
