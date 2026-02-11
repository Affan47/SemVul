get_type(struct blkdev_cxt *cxt)
{
	char *res = NULL, *p;

	if (is_dm(cxt->name)) {
		char *dm_uuid = sysfs_strdup(&cxt->sysfs, "dm/uuid");


		if (dm_uuid) {
			char *tmp = dm_uuid;
			char *dm_uuid_prefix = strsep(&tmp, "-");

			if (dm_uuid_prefix) {

				if (strncasecmp(dm_uuid_prefix, "part", 4) == 0)
					dm_uuid_prefix[4] = '\0';

				res = xstrdup(dm_uuid_prefix);
			}
		}

		free(dm_uuid);
		if (!res)

			res = xstrdup("dm");

	} else if (!strncmp(cxt->name, "loop", 4)) {
		res = xstrdup("loop");

	} else if (!strncmp(cxt->name, "md", 2)) {
		char *md_level = sysfs_strdup(&cxt->sysfs, "md/level");
		res = md_level ? md_level : xstrdup("md");

	} else {
		const char *type = cxt->partition ? "part" : "disk";
		int x = 0;

		sysfs_read_int(&cxt->sysfs, "device/type", &x);

		switch (x) {
			case 0x0c:
				type = "raid"; break;
			case 0x01:
				type = "raid"; break;
			case 0x04:
			case 0x05:
				type = "rom"; break;
			case 0x07:
				type = "mo-disk"; break;
			case 0x0e:
				type = "rbc"; break;
		}

		res = xstrdup(type);
	}

	for (p = res; p && *p; p++)
		*p = tolower((unsigned char) *p);
	return res;
}
