isns_create_db_keystore(isns_db_t *db)
{
	isns_db_keystore_t *store;
	isns_object_t	*entity;

	isns_debug_auth("Creating DB keystore\n");
	if (!(entity = isns_db_get_control(db))) {
		isns_error("Could not create control entity in database\n");
		return NULL;
	}
	isns_debug_auth("Control entity is 0x%08x\n", entity->ie_index);

	store = isns_calloc(1, sizeof(*store));
	store->sd_base.ic_name = "database key store";
	store->sd_base.ic_find = __isns_db_keystore_find;
	store->sd_base.ic_get_policy = __isns_db_keystore_get_policy;
	store->sd_control = entity;
	store->sd_db = db;

	isns_register_callback(__isns_db_keystore_change_notify, store);

	return (isns_keystore_t *) store;
}
