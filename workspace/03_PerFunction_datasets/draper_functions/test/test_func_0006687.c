parse_mount_options(struct ceph_mount_options **pfsopt,
			       struct ceph_options **popt,
			       int flags, char *options,
			       const char *dev_name,
			       const char **path)
{
	struct ceph_mount_options *fsopt;
	const char *dev_name_end;
	int err;

	if (!dev_name || !*dev_name)
		return -EINVAL;

	fsopt = kzalloc(sizeof(*fsopt), GFP_KERNEL);
	if (!fsopt)
		return -ENOMEM;

	dout("parse_mount_options %p, dev_name '%s'\n", fsopt, dev_name);

	fsopt->sb_flags = flags;
	fsopt->flags = CEPH_MOUNT_OPT_DEFAULT;

	fsopt->rsize = CEPH_RSIZE_DEFAULT;
	fsopt->rasize = CEPH_RASIZE_DEFAULT;
	fsopt->snapdir_name = kstrdup(CEPH_SNAPDIRNAME_DEFAULT, GFP_KERNEL);
	if (!fsopt->snapdir_name) {
		err = -ENOMEM;
		goto out;
	}

	fsopt->caps_wanted_delay_min = CEPH_CAPS_WANTED_DELAY_MIN_DEFAULT;
	fsopt->caps_wanted_delay_max = CEPH_CAPS_WANTED_DELAY_MAX_DEFAULT;
	fsopt->cap_release_safety = CEPH_CAP_RELEASE_SAFETY_DEFAULT;
	fsopt->max_readdir = CEPH_MAX_READDIR_DEFAULT;
	fsopt->max_readdir_bytes = CEPH_MAX_READDIR_BYTES_DEFAULT;
	fsopt->congestion_kb = default_congestion_kb();


	dev_name_end = strchr(dev_name, '/');
	if (dev_name_end) {

		*path = dev_name_end + 1;
	} else {

		dev_name_end = dev_name + strlen(dev_name);
		*path = dev_name_end;
	}
	err = -EINVAL;
	dev_name_end--;
	if (dev_name_end < dev_name || *dev_name_end != ':') {
		pr_err("device name is missing path (no : separator in %s)\n",
				dev_name);
		goto out;
	}
	dout("device name '%.*s'\n", (int)(dev_name_end - dev_name), dev_name);
	dout("server path '%s'\n", *path);

	*popt = ceph_parse_options(options, dev_name, dev_name_end,
				 parse_fsopt_token, (void *)fsopt);
	if (IS_ERR(*popt)) {
		err = PTR_ERR(*popt);
		goto out;
	}


	*pfsopt = fsopt;
	return 0;

out:
	destroy_mount_options(fsopt);
	return err;
}
