probe_one(blkid_cache cache, const char *ptname,
		      dev_t devno, int pri, int only_if_new, int removable)
{
	blkid_dev dev = NULL;
	struct list_head *p, *pnext;
	const char **dir;
	char *devname = NULL;


	list_for_each_safe(p, pnext, &cache->bic_devs) {
		blkid_dev tmp = list_entry(p, struct blkid_struct_dev,
					   bid_devs);
		if (tmp->bid_devno == devno) {
			if (only_if_new && !access(tmp->bid_name, F_OK))
				return;
			dev = blkid_verify(cache, tmp);
			if (dev && (dev->bid_flags & BLKID_BID_FL_VERIFIED))
				break;
			dev = 0;
		}
	}
	if (dev && dev->bid_devno == devno)
		goto set_pri;


	if (!strncmp(ptname, "dm-", 3) && isdigit(ptname[3])) {
		devname = canonicalize_dm_name(ptname);
		if (!devname)
			blkid__scan_dir("/dev/mapper", devno, 0, &devname);
		if (devname)
			goto get_dev;
	}


	for (dir = dirlist; *dir; dir++) {
		struct stat st;
		char device[256];

		sprintf(device, "%s/%s", *dir, ptname);
		if ((dev = blkid_get_dev(cache, device, BLKID_DEV_FIND)) &&
		    dev->bid_devno == devno)
			goto set_pri;

		if (stat(device, &st) == 0 &&
		    (S_ISBLK(st.st_mode) ||
		     (S_ISCHR(st.st_mode) && !strncmp(ptname, "ubi", 3))) &&
		    st.st_rdev == devno) {
			devname = blkid_strdup(device);
			goto get_dev;
		}
	}

	if (!devname)
		blkid__scan_dir("/dev/mapper", devno, 0, &devname);
	if (!devname) {
		devname = blkid_devno_to_devname(devno);
		if (!devname)
			return;
	}

get_dev:
	dev = blkid_get_dev(cache, devname, BLKID_DEV_NORMAL);
	free(devname);

set_pri:
	if (dev) {
		if (pri)
			dev->bid_pri = pri;
		else if (!strncmp(dev->bid_name, "/dev/mapper/", 11)) {
			dev->bid_pri = BLKID_PRI_DM;
			if (is_dm_leaf(ptname))
				dev->bid_pri += 5;
		} else if (!strncmp(ptname, "md", 2))
			dev->bid_pri = BLKID_PRI_MD;
		if (removable)
			dev->bid_flags |= BLKID_BID_FL_REMOVABLE;
	}
	return;
}
