evalstatus(n)
int n;
{
	if (n < 0) return(FNC_CANCEL);
	if (internal_status == FNC_QUIT || internal_status > FNC_CANCEL)
		return(internal_status);

	return(FNC_EFFECT);
}
