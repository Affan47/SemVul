probe_gfs2(blkid_probe pr, const struct blkid_idmag *mag)
{
	struct gfs2_sb *sbd;

	sbd = blkid_probe_get_sb(pr, mag, struct gfs2_sb);
	if (!sbd)
		return errno ? -errno : 1;

	if (be32_to_cpu(sbd->sb_fs_format) == GFS2_FORMAT_FS &&
	    be32_to_cpu(sbd->sb_multihost_format) == GFS2_FORMAT_MULTI)
	{
		if (*sbd->sb_locktable)
			blkid_probe_set_label(pr,
				(unsigned char *) sbd->sb_locktable,
				sizeof(sbd->sb_locktable));
		blkid_probe_set_uuid(pr, sbd->sb_uuid);
		blkid_probe_set_version(pr, "1");
		return 0;
	}
	return 1;
}
