delete_temp_files(sl* tempfiles, sl* tempdirs) {
	int i;
	for (i=0; i<sl_size(tempfiles); i++) {
		char* fn = sl_get(tempfiles, i);
		logverb("Deleting temp file %s\n", fn);
		if (unlink(fn))
			SYSERROR("Failed to delete temp file \"%s\"", fn);
	}
	for (i=0; i<sl_size(tempdirs); i++) {
		char* fn = sl_get(tempdirs, i);
		logverb("Deleting temp dir %s\n", fn);
		if (rmdir(fn))
			SYSERROR("Failed to delete temp dir \"%s\"", fn);
	}
	sl_remove_all(tempfiles);
	sl_remove_all(tempdirs);
}
