str_to_device_type(char *str)
{
	if (!strcmp(str, "disk"))
		return TYPE_DISK;
	else if (!strcmp(str, "tape"))
		return TYPE_TAPE;
	else if (!strcmp(str, "cd"))
		return TYPE_MMC;
	else if (!strcmp(str, "changer"))
		return TYPE_MEDIUM_CHANGER;
	else if (!strcmp(str, "osd"))
		return TYPE_OSD;
	else if (!strcmp(str, "ssc"))
		return TYPE_TAPE;
	else if (!strcmp(str, "pt"))
		return TYPE_PT;
	else {
		eprintf("unknown target type: %s\n", str);
		exit(EINVAL);
	}
}
