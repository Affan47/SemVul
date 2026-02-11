fat_utime(File_t *F, struct utimbuf *buf) {
	if ((F==NULL)||(buf==NULL)) return -1;
	WORD accdate, acctime, moddate, modtime;

	fat_fill_time(&accdate, &acctime, buf->actime);
	fat_fill_time(&moddate, &modtime, buf->modtime);
	F->DirEntry->DIR_LstAccDate = accdate;
	F->DirEntry->DIR_WrtDate 	= moddate;
	F->DirEntry->DIR_WrtTime 	= modtime;
	return (fat_update_file(F));
}
