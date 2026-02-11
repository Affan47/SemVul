xfrm_reqid_parse(__u32 *reqid, int *argcp, char ***argvp)
{
	int argc = *argcp;
	char **argv = *argvp;

	if (get_u32(reqid, *argv, 0))
		invarg("REQID value is invalid", *argv);

	*argcp = argc;
	*argvp = argv;

	return 0;
}
