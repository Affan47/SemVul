relative_delete (cob_file *f)
{
	size_t	relsize;
	int	relnum;
	off_t	off;
#ifdef	WITH_SEQRA_EXTFH
	int	extfh_ret;

	extfh_ret = extfh_relative_delete (f);
	if (extfh_ret != COB_NOT_CONFIGURED) {
		return extfh_ret;
	}
#endif

	relnum = cob_get_int (f->keys[0].field) - 1;
	relsize = f->record_max + sizeof (f->record->size);
	off = relnum * relsize;
	if (fseek ((FILE *)f->file, off, SEEK_SET) != 0 ||
	    fread (&f->record->size, sizeof (f->record->size),
		   1, (FILE *)f->file) != 1) {
			return COB_STATUS_23_KEY_NOT_EXISTS;
	}
	fseek ((FILE *)f->file, - (off_t) sizeof (f->record->size), SEEK_CUR);

	f->record->size = 0;
	if (fwrite (&f->record->size, sizeof (f->record->size), 1, (FILE *)f->file) != 1) {
		return COB_STATUS_30_PERMANENT_ERROR;
	}
	fseek ((FILE *)f->file, (off_t) f->record_max, SEEK_CUR);
	return COB_STATUS_00_SUCCESS;
}
