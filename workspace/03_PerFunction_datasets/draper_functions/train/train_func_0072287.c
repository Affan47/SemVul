savestate_initsave (const TCHAR *filename, int mode, int nodialogs, bool save)
{
	if (filename == NULL) {
		savestate_fname[0] = 0;
		savestate_docompress = 0;
		savestate_specialdump = 0;
		savestate_nodialogs = 0;
		return;
	}
	_tcscpy (savestate_fname, filename);
	savestate_docompress = (mode == 1) ? 1 : 0;
	savestate_specialdump = (mode == 3) ? 1 : (mode == 4) ? 2 : 0;
	savestate_nodialogs = nodialogs;
	new_blitter = false;
	if (save) {
		savestate_free ();
		inprec_close (true);
	}
}
