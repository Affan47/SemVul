n_cmd(File *f, Cmd *cp)
{
	int i;
	USED(f);
	USED(cp);
	for(i = 0; i<file.nused; i++){
		if(file.filepptr[i] == cmd)
			continue;
		f = file.filepptr[i];
		Strduplstr(&genstr, &f->name);
		filename(f);
	}
	return TRUE;
}
