tc_class_list(int argc, char **argv)
{
	struct tcmsg t;
	char d[16];

	memset(&t, 0, sizeof(t));
	t.tcm_family = AF_UNSPEC;
	memset(d, 0, sizeof(d));

	filter_qdisc = 0;
	filter_classid = 0;

	while (argc > 0) {
		if (strcmp(*argv, "dev") == 0) {
			NEXT_ARG();
			if (d[0])
				duparg("dev", *argv);
			strncpy(d, *argv, sizeof(d)-1);
		} else if (strcmp(*argv, "qdisc") == 0) {
			NEXT_ARG();
			if (filter_qdisc)
				duparg("qdisc", *argv);
			if (get_qdisc_handle(&filter_qdisc, *argv))
				invarg("invalid qdisc ID", *argv);
		} else if (strcmp(*argv, "classid") == 0) {
			NEXT_ARG();
			if (filter_classid)
				duparg("classid", *argv);
			if (get_tc_classid(&filter_classid, *argv))
				invarg("invalid class ID", *argv);
		} else if (strcmp(*argv, "root") == 0) {
			if (t.tcm_parent) {
				fprintf(stderr, "Error: \"root\" is duplicate parent ID\n");
				return -1;
			}
			t.tcm_parent = TC_H_ROOT;
		} else if (strcmp(*argv, "parent") == 0) {
			__u32 handle;
			if (t.tcm_parent)
				duparg("parent", *argv);
			NEXT_ARG();
			if (get_tc_classid(&handle, *argv))
				invarg("invalid parent ID", *argv);
			t.tcm_parent = handle;
		} else if (matches(*argv, "help") == 0) {
			usage();
		} else {
			fprintf(stderr, "What is \"%s\"? Try \"tc class help\".\n", *argv);
			return -1;
		}

		argc--; argv++;
	}

 	ll_init_map(&rth);

	if (d[0]) {
		if ((t.tcm_ifindex = ll_name_to_index(d)) == 0) {
			fprintf(stderr, "Cannot find device \"%s\"\n", d);
			return 1;
		}
		filter_ifindex = t.tcm_ifindex;
	}

 	if (rtnl_dump_request(&rth, RTM_GETTCLASS, &t, sizeof(t)) < 0) {
		perror("Cannot send dump request");
		return 1;
	}

 	if (rtnl_dump_filter(&rth, print_class, stdout) < 0) {
		fprintf(stderr, "Dump terminated\n");
		return 1;
	}

	return 0;
}
