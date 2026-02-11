create_browser(const char *fname)
{
	curfile = open_shape_file(fname);
	if (!curfile)
		return 0;
	Object_browser *chooser = curfile->get_browser(vgafile, palbuf);
	setup_groups();
	return chooser;
}
