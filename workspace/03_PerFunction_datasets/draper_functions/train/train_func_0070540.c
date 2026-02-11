name(const char *fname)
{
	do_remove=0;
	if (filename)
		delete[] filename;
	if (!fname)
	{
		filename=0;
		return;
	}

	filename=new char[strlen(fname)+1];

	if (!filename)	outofmem();
	strcpy(filename, fname);
	do_remove=1;
}
