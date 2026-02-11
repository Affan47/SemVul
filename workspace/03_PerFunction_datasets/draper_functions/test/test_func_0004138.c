find_boot_flag(char *subsys, char *list[], ssize_t size,
			  int *boot_idx)
{
	int rc = ENODEV;
	int i, flag = 0;

	for (i = 0; i < size; i++, flag = -1) {
		rc = sysfs_get_int(list[i], subsys, "flags", &flag);
		if (rc)
			continue;

		if (flag & IBFT_SYSFS_FLAG_FW_SEL_BOOT) {
			*boot_idx = i;
			rc = 0;
			break;
		}
		rc = ENODEV;
		flag = 0;

	}

	return rc;
}
