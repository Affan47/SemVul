load(File *f)
{
	Address saveaddr;

	Strduplstr(&genstr, &f->name);
	filename(f);
	if(f->name.s[0]){
		saveaddr = addr;
		edit(f, 'I');
		addr = saveaddr;
	}else{
		f->unread = 0;
		f->cleanseq = f->seq;
	}

	fileupdate(f, TRUE, TRUE);
}
