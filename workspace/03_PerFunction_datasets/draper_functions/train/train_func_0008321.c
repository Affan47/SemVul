getcharid(FILEID id)
{
	FILEIO *fiop;
	FILEPOS fpos;

	fiop = findid(id, FALSE);
	if (fiop == NULL)
		return -2;
	if (fiop->action == 'w') {
		f_tell(fiop->fp, &fpos);
		fflush(fiop->fp);
		if (f_seek_set(fiop->fp, &fpos) < 0)
			return -3;
	}
	fiop->action = 'r';

	return fgetc(fiop->fp);
}
