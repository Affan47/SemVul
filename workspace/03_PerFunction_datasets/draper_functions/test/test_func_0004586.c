create_memory_device(dev_t dev)
{
	struct stat stat;

	if (file_exists(pc->live_memsrc, &stat)) {


		if ((stat.st_mode == MEMORY_DRIVER_DEVICE_MODE) &&
		    (stat.st_rdev == dev))
			return TRUE;


		if (!S_ISCHR(stat.st_mode))
			error(FATAL,
			    "%s: not a character device -- please delete it!\n",
				pc->live_memsrc);
		else if (dev != stat.st_rdev)
			error(FATAL,
			    "%s: invalid device: %d/%d  -- please delete it!\n",
				pc->live_memsrc, major(stat.st_rdev),
				minor(stat.st_rdev));
		else
			unlink(pc->live_memsrc);
	}


	if (mknod(pc->live_memsrc, MEMORY_DRIVER_DEVICE_MODE, dev)) {
		error(INFO, "%s: mknod: %s\n", pc->live_memsrc,
			strerror(errno));
		return FALSE;
	}

	return TRUE;
}
