sg_fs_stats_item_compare(const sg_fs_stats *a, const sg_fs_stats *b) {

	int rc;

	rc = strcmp(a->device_name, b->device_name);
	if( 0 != rc )
		return rc;

	rc = strcmp(a->device_canonical, b->device_canonical);
	if( 0 != rc )
		return rc;

	rc = strcmp(a->mnt_point, b->mnt_point);
	if( 0 != rc )
		return rc;

	rc = strcmp(a->fs_type, b->fs_type);
	if( 0 != rc )
		return rc;

	return 0;
}
