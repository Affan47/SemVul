db_write_str(database_handle_t *db, const char *str)
{
	return_val_if_fail(db != NULL, false);
	return_val_if_fail(db->vt != NULL, false);
	return_val_if_fail(db->vt->write_str != NULL, false);

	return db->vt->write_str(db, str);
}
