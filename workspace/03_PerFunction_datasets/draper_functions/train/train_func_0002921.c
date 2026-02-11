cst_wave_load_riff(cst_wave *w,const char *filename)
{
    cst_file fd;
    int r;

    if ((fd = cst_fopen(filename,CST_OPEN_READ|CST_OPEN_BINARY)) == NULL)
    {
	cst_errmsg("cst_wave_load: can't open file \"%s\"\n",
		   filename);
	return -1;
    }

    r = cst_wave_load_riff_fd(w,fd);

    cst_fclose(fd);

    return r;
}
