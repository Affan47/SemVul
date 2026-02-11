swan_vk_parse_option(struct swan_vk_command_option *opt, int argc, char *argv[])
{
	int c;
	int option_index;
	struct option long_option[] =
	{
		{
			.name = "serial",
			.has_arg = required_argument,
			.flag = NULL,
			.val = 's',
		},
		{
			.name = "usb",
			.has_arg = no_argument,
			.flag = NULL,
			.val = 'u',
		},
		{
			.name = "adb",
			.has_arg = no_argument,
			.flag = NULL,
			.val = 'u',
		},
		{
			.name = "tcp",
			.has_arg = no_argument,
			.flag = NULL,
			.val = 't',
		},
		{
			.name = "ip",
			.has_arg = required_argument,
			.flag = NULL,
			.val = 'i',
		},
		{
			.name = "port",
			.has_arg = required_argument,
			.flag = NULL,
			.val = 'p',
		},
		{
			.name = "daemon",
			.has_arg = no_argument,
			.flag = NULL,
			.val = 'd',
		},
		{
			.name = "local",
			.has_arg = optional_argument,
			.flag = NULL,
			.val = 'l',
		},
		{
			0, 0, 0, 0
		},
	};

	opt->link_type = SWAN_VK_LINK_ADB;
	opt->ip[0] = 0;
	opt->port = SWAN_VK_TCP_PORT;
	opt->as_daemon = false;

	while ((c = getopt_long(argc, argv, "S:s:UuTtP:p:I:i:DdL::l::", long_option, &option_index)) != EOF)
	{
		switch (c)
		{
		case 's':
		case 'S':
			text_copy(opt->devpath, optarg);
			opt->link_type = SWAN_VK_LINK_SERIAL;
			break;

		case 'u':
		case 'U':
			opt->link_type = SWAN_VK_LINK_ADB;
			break;

		case 't':
		case 'T':
			opt->link_type = SWAN_VK_LINK_TCP;
			break;

		case 'i':
		case 'I':
			text_copy(opt->ip, optarg);
			break;

		case 'p':
		case 'P':
			opt->port = text2value_unsigned(optarg, NULL, 10);
			break;

		case 'd':
		case 'D':
			opt->as_daemon = true;
			break;

		case 'l':
		case 'L':
			opt->link_type = SWAN_VK_LINK_LOCAL;
			if (optarg == NULL)
			{
				optarg = DEVICE_SWAN_VK_DATA;
			}

			text_copy(opt->devpath, optarg);
			break;

		default:
			pr_red_info("Unknown option");
			return -EINVAL;
		}
	}

	if (opt->ip[0] == 0)
	{
		text_copy(opt->ip, "127.0.0.1");
	}

	return optind;
}
