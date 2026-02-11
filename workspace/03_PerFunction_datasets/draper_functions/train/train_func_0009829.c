create_share (guint conn_type)
{
	char *name = dmap_sharing_default_share_name ();
	DMAPContainerRecord *dmap_container_record = \
		DMAP_CONTAINER_RECORD (test_dmap_container_record_new ());
	DMAPContainerDb *dmap_container_db = \
		DMAP_CONTAINER_DB (test_dmap_container_db_new
					(dmap_container_record));
	DMAPRecordFactory *factory;
	DMAPRecord *record;
	DMAPShare *share;
	DMAPDb *db;

	if (conn_type == DAAP) {
		factory = DMAP_RECORD_FACTORY (test_daap_record_factory_new ());

	} else {
		factory = DMAP_RECORD_FACTORY (test_dpap_record_factory_new ());
	}

	record = DMAP_RECORD (dmap_record_factory_create (factory, NULL));
	db = DMAP_DB (test_dmap_db_new ());
	dmap_db_add (db, record);
	g_object_unref (record);

	g_warning ("initialize DAAP sharing");

	if (conn_type == DAAP) {
		share = DMAP_SHARE (daap_share_new (name,
						    NULL,
						    db,
						    dmap_container_db,
						    NULL));
	} else {
		share = DMAP_SHARE (dpap_share_new (name,
						    NULL,
						    db,
						    dmap_container_db,
						    NULL));
	}

	g_free (name);
}
