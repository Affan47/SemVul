do_if_print(struct interface *ife)
{
	int res;

	res = do_if_fetch(ife);
	if (res >= 0) {
		if ((ife->flags & IFF_UP) || interface_opt_a)
			ife_print(ife);
	}
	return res;
}
