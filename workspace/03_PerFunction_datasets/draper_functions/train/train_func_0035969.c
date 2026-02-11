cf_open_fill_cfblock(FILE *fp, int type)
{
	int cfile_block_index;

	cfile_block_index = cfget_cfile_block();
	if ( cfile_block_index == -1 ) {
		fclose(fp);
		return NULL;
	} else {
		CFILE *cfp;
		Cfile_block *cfbp;
		cfbp = &Cfile_block_list[cfile_block_index];
		cfp = &Cfile_list[cfile_block_index];
		cfp->id = cfile_block_index;
		cfp->version = 0;
		cfbp->data = NULL;
		cfbp->fp = fp;
		cfbp->dir_type = type;
		cfbp->max_read_len = 0;

		int pos = ftell(fp);
		if(pos == -1L)
			pos = 0;
		cf_init_lowlevel_read_code(cfp,0,filelength(fileno(fp)), 0 );

		return cfp;
	}
}
