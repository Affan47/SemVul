probe_ext4(blkid_probe pr,
		const struct blkid_idmag *mag __attribute__((__unused__)))
{
	struct ext2_super_block *es;
	uint32_t fc, frc, fi;

	es = ext_get_super(pr, &fc, &fi, &frc);
	if (!es)
		return errno ? -errno : 1;


	if (fi & EXT3_FEATURE_INCOMPAT_JOURNAL_DEV)
		return 1;


	if (!(frc & EXT3_FEATURE_RO_COMPAT_UNSUPPORTED) &&
	    !(fi  & EXT3_FEATURE_INCOMPAT_UNSUPPORTED))
		return 1;


	if (le32_to_cpu(es->s_flags) & EXT2_FLAGS_TEST_FILESYS)
		return 1;

	ext_get_info(pr, 4, es);
	return 0;
}
