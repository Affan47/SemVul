probe_romfs(blkid_probe pr, const struct blkid_idmag *mag)
{
	struct romfs_super_block *ros;

	ros = blkid_probe_get_sb(pr, mag, struct romfs_super_block);
	if (!ros)
		return -1;

	if (strlen((char *) ros->ros_volume))
		blkid_probe_set_label(pr, ros->ros_volume,
				sizeof(ros->ros_volume));
	return 0;
}
