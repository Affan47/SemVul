list_backups(ext2_filsys fs, unsigned int *three,
				 unsigned int *five, unsigned int *seven)
{
	unsigned int *min = three;
	int mult = 3;
	unsigned int ret;

	if (!(fs->super->s_feature_ro_compat &
	      EXT2_FEATURE_RO_COMPAT_SPARSE_SUPER)) {
		ret = *min;
		*min += 1;
		return ret;
	}

	if (*five < *min) {
		min = five;
		mult = 5;
	}
	if (*seven < *min) {
		min = seven;
		mult = 7;
	}

	ret = *min;
	*min *= mult;

	return ret;
}
