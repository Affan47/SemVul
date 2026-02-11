set_target_parse(int c, char **argv, int invert, unsigned int *flags,
		 const void *entry, struct xt_entry_target **target)
{
	struct xt_set_info_target *myinfo =
		(struct xt_set_info_target *) (*target)->data;

	switch (c) {
	case '1':
		parse_target(argv, invert, flags,
			     &myinfo->add_set, "add-set");
		break;
	case '2':
		parse_target(argv, invert, flags,
			     &myinfo->del_set, "del-set");
		break;
	}
	return 1;
}
