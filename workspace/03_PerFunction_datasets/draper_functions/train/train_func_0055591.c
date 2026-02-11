probe_devices ( void ) {
	struct root_device *rootdev;
	int rc;

	for_each_table_entry ( rootdev, ROOT_DEVICES ) {
		list_add ( &rootdev->dev.siblings, &devices );
		INIT_LIST_HEAD ( &rootdev->dev.children );
		if ( ( rc = rootdev_probe ( rootdev ) ) != 0 )
			list_del ( &rootdev->dev.siblings );
	}
}
