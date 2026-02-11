xfrm_policy_get(int argc, char **argv)
{
	char buf[NLMSG_BUF_SIZE];
	struct nlmsghdr *n = (struct nlmsghdr *)buf;

	memset(buf, 0, sizeof(buf));

	xfrm_policy_get_or_delete(argc, argv, 0, n);

	if (xfrm_policy_print(NULL, n, (void*)stdout) < 0) {
		fprintf(stderr, "An error :-)\n");
		exit(1);
	}

	return 0;
}
