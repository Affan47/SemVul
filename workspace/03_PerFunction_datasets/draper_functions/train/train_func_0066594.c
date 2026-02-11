lvm_get_devno(const char *lvm_device)
{
	FILE *lvf;
	char buf[1024];
	int ma, mi;
	dev_t ret = 0;

	DBG(DEVNAME, ul_debug("opening %s", lvm_device));
	if ((lvf = fopen(lvm_device, "r" UL_CLOEXECSTR)) == NULL) {
		DBG(DEVNAME, ul_debug("%s: (%d) %m", lvm_device, errno));
		return 0;
	}

	while (fgets(buf, sizeof(buf), lvf)) {
		if (sscanf(buf, "device: %d:%d", &ma, &mi) == 2) {
			ret = makedev(ma, mi);
			break;
		}
	}
	fclose(lvf);

	return ret;
}
