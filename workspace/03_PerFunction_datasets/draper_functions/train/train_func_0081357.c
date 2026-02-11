snpbus_remove ( struct root_device *rootdev __unused ) {
	snpnet_remove ( &snponly_dev );
	list_del ( &snponly_dev.dev.siblings );
}
