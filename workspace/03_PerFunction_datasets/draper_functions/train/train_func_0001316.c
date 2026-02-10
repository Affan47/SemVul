launch_file(arg)
CONST char *arg;
{
	if (!launcher()) return(view_file(arg));

	return(FNC_EFFECT);
}
