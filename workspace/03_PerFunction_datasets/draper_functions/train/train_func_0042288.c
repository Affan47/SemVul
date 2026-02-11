generate_securid_tokencodes(struct openconnect_info *vpninfo)
{


	static int got_from_env = 0;

	if (!got_from_env) {
		char *t1, *t2;

		got_from_env = 1;

		t1 = getenv("SID_TOKEN1");
		t2 = getenv("SID_TOKEN2");

		if (t1 && t2) {
			strncpy(vpninfo->sid_tokencode, t1, 8);
			strncpy(vpninfo->sid_nexttokencode, t2, 8);
			return 0;
		}
	}
	return -EINVAL;
}
