inotifytools_filename_from_wd( int wd ) {
	niceassert( init, "inotifytools_initialize not called yet" );
	watch *w = watch_from_wd(wd);
	if (!w)
        return NULL;

	return w->filename;
}
