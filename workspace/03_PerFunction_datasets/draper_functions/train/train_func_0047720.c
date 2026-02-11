flushid(FILEID id)
{
	FILEIO *fiop;

	fiop = findid(id, -1);
	if (fiop == NULL)
		return 0;
	if (!fiop->writing || fiop->action == 'r')
		return 0;
	return fflush(fiop->fp);
}
