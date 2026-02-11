isns_db_purge(isns_db_t *db)
{
	isns_object_list_t *list = &db->id_deferred;
	unsigned int	i;

	while (list->iol_count) {
		isns_object_t *obj = list->iol_data[0];

		if (obj->ie_references == 0) {
			isns_debug_state("DB: destroying object %u (%s)\n",
					obj->ie_index,
					obj->ie_template->iot_name);

			if (db->id_backend) {
				db->id_backend->idb_remove(db, obj);

			}

			isns_object_list_remove(db->id_objects, obj);
			obj->ie_state = ISNS_OBJECT_STATE_DEAD;
		} else if (obj->ie_state != ISNS_OBJECT_STATE_LIMBO) {
			isns_debug_state("DB: moving object %u (%s) to purgatory - "
					"%u references left\n",
					obj->ie_index,
					obj->ie_template->iot_name,
					obj->ie_references);

			isns_object_list_append(&db->id_limbo, obj);
			obj->ie_state = ISNS_OBJECT_STATE_LIMBO;
			isns_object_prune_attrs(obj);

			if (db->id_backend) {
				db->id_backend->idb_store(db, obj);
				db->id_backend->idb_sync(db);
			}
		}

		isns_object_list_remove(list, obj);
	}


	for (i = 0; i < db->id_limbo.iol_count; ) {
		isns_object_t *obj = db->id_limbo.iol_data[i];

		if (obj->ie_references == 0) {
			isns_debug_state("DB: destroying object %u (%s)\n",
					obj->ie_index,
					obj->ie_template->iot_name);

			if (db->id_backend) {
				db->id_backend->idb_remove(db, obj);

			}

			obj->ie_state = ISNS_OBJECT_STATE_DEAD;
			isns_object_list_remove(&db->id_limbo, obj);
			isns_object_list_remove(db->id_objects, obj);
			continue;
		}

		i += 1;
	}
}
