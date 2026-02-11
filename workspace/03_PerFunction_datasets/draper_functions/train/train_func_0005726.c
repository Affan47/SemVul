_display_name(CMD_ARGS)
{
	char dev_name[PATH_MAX];

	if (!names)
		return 1;

	if ((_dev_name_type == DN_BLK || _dev_name_type == DN_MAP) &&
	    dm_device_get_name((int) MAJOR(names->dev), (int) MINOR(names->dev),
			       _dev_name_type == DN_BLK, dev_name, PATH_MAX))
		printf("%s\t(%s)\n", names->name, dev_name);
	else
		printf("%s\t(%d:%d)\n", names->name,
					(int) MAJOR(names->dev),
					(int) MINOR(names->dev));

	return 1;
}
