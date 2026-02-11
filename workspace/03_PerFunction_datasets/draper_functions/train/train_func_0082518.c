restore_zram (int len, size_t filepos, int num)
{
	if (num == -1) {
		z3_fileposchip = filepos;
		changed_prefs.z3chipmem_size = len;
	} else if (num == 1) {
		z3_filepos2 = filepos;
		changed_prefs.z3fastmem2_size = len;
	} else {
		z3_filepos = filepos;
		changed_prefs.z3fastmem_size = len;
	}
}
