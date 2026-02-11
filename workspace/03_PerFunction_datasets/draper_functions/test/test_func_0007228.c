parse_fmt(char *optarg, __u32 &width, __u32 &height, __u32 &pixelformat)
{
	char *value, *subs;
	int fmts = 0;

	subs = optarg;
	while (*subs != '\0') {
		static const char *const subopts[] = {
			"width",
			"height",
			"pixelformat",
			NULL
		};

		switch (parse_subopt(&subs, subopts, &value)) {
		case 0:
			width = strtol(value, 0L, 0);
			fmts |= FmtWidth;
			break;
		case 1:
			height = strtol(value, 0L, 0);
			fmts |= FmtHeight;
			break;
		case 2:
			if (strlen(value) == 4)
				pixelformat =
					v4l2_fourcc(value[0], value[1],
							value[2], value[3]);
			else
				pixelformat = strtol(value, 0L, 0);
			fmts |= FmtPixelFormat;
			break;
		default:
			return 0;
		}
	}
	return fmts;
}
