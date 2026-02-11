iscsi_sysfs_get_host_no_from_sid(uint32_t sid, int *err)
{
	struct sysfs_device *session_dev, *host_dev;
	char devpath[PATH_SIZE];
	char id[NAME_SIZE];

	*err = 0;
	snprintf(id, sizeof(id), "session%u", sid);
	if (!sysfs_lookup_devpath_by_subsys_id(devpath, sizeof(devpath),
					       ISCSI_SESSION_SUBSYS, id)) {
		log_error("Could not lookup devpath for %s. Possible sysfs "
			  "incompatibility.\n", id);
		*err = ISCSI_ERR_SYSFS_LOOKUP;
		return 0;
	}

	session_dev = sysfs_device_get(devpath);
	if (!session_dev) {
		log_error("Could not get dev for %s. Possible sysfs "
			  "incompatibility.\n", id);
		*err = ISCSI_ERR_SYSFS_LOOKUP;
		return 0;
	}


	host_dev = sysfs_device_get_parent_with_subsystem(session_dev,
							  SCSI_SUBSYS);
	if (!host_dev) {
		struct sysfs_device *dev_parent;

		dev_parent = sysfs_device_get_parent(session_dev);
		while (dev_parent != NULL) {
			if (strncmp(dev_parent->kernel, "host", 4) == 0) {
				host_dev = dev_parent;
				break;
			}
			dev_parent = sysfs_device_get_parent(dev_parent);
		}

		if (!host_dev) {
			log_error("Could not get host dev for %s. Possible "
				  "sysfs incompatibility.\n", id);
			*err = ISCSI_ERR_SYSFS_LOOKUP;
			return 0;
		}
	}

	return atol(host_dev->kernel_number);
}
