check_abi_version(const char *path)
{
	char value[8];

	if (ibv_read_sysfs_file(path, "class/infiniband_verbs/abi_version",
				value, sizeof value) < 0) {
		return ENOSYS;
	}

	abi_ver = strtol(value, NULL, 10);

	if (abi_ver < IB_USER_VERBS_MIN_ABI_VERSION ||
	    abi_ver > IB_USER_VERBS_MAX_ABI_VERSION) {
		fprintf(stderr, PFX "Fatal: kernel ABI version %d "
			"doesn't match library version %d.\n",
			abi_ver, IB_USER_VERBS_MAX_ABI_VERSION);
		return ENOSYS;
	}

	return 0;
}
