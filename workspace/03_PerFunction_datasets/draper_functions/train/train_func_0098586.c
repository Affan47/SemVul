edit_config(arg)
CONST char *arg;
{
	if (!arg && FILEPERROW < WFILEMINCUSTOM) {
		warning(0, NOROW_K);
		return(FNC_CANCEL);
	}
	if (customize(arg) <= 0) return(FNC_CANCEL);

	return(FNC_EFFECT);
}
