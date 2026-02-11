setAccessModeInternal(IOAccessMode am)
{

	if (getAccessMode() == am) return 0;

	int e = 0;
	if (am != IOAM_NULL) {
		pstat_t s;
		if (file) {
			file = sys_freopen(mFilename.contentChar(), mOpenMode, am, file);
			if (!file) setAccessMode(IOAM_NULL);
		} else {
			file = sys_fopen(mFilename.contentChar(), mOpenMode, am);
		}
		if (!file) e = errno;
		if (!e) {
			own_file = true;
			e = sys_pstat_file(s, file);
			if (!e) {
				if (HT_S_ISDIR(s.mode)) {
					e = EISDIR;
				} else if (!HT_S_ISREG(s.mode) && !HT_S_ISBLK(s.mode)) {
					e = EINVAL;
				}
			}
		}
	} else {
		if (file) {
			sys_fclose(file);
			file = NULL;
		}
	}
	return e ? e : File::setAccessMode(am);
}
