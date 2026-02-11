write_dir(arg)
CONST char *arg;
{
	int fs;

	if (writefs >= 2 || findpattern) return(warning_bell(arg));
	if ((fs = writablefs(curpath)) <= 0) {
		warning(0, NOWRT_K);
		return(FNC_CANCEL);
	}
	if (!yesno(WRTOK_K)) return(FNC_CANCEL);
	if (underhome(NULL) <= 0 && !yesno(HOMOK_K)) return(FNC_CANCEL);
	arrangedir(fs);
	chgorder = 0;

	return(FNC_EFFECT);
}
