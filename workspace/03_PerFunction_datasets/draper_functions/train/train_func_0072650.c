alloc_multidata_if_needed(filestruct *fileptr)
{
    if (!fileptr->multidata)
	fileptr->multidata = (short *) nmalloc(openfile->syntax->nmultis * sizeof(short));
}
