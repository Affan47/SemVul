isns_db_insert_limbo(isns_db_t *db, isns_object_t *obj)
{
	isns_assert(obj->ie_state == ISNS_OBJECT_STATE_LARVAL);
	__isns_db_insert(db, obj, ISNS_OBJECT_STATE_LIMBO);
}
