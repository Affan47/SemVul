isdir(void) {
    STATBUF sb;
    if(CLAMSTAT(actarget, &sb) || !S_ISDIR(sb.st_mode)) {
	logg("!'%s' doesn't exist or is not a directory\n", actarget);
	return 0;
    }
    return 1;
}
