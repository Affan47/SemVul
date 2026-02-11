_pack_accounting_update_msg(accounting_update_msg_t *msg,
					Buf buffer,
					uint16_t protocol_version)
{
	uint32_t count = 0;
	ListIterator itr = NULL;
	slurmdb_update_object_t *rec = NULL;


	if (msg->rpc_version >= 8) {
		pack16(msg->rpc_version, buffer);
		if (msg->update_list)
			count = list_count(msg->update_list);

		pack32(count, buffer);

		if (count) {
			itr = list_iterator_create(msg->update_list);
			while ((rec = list_next(itr))) {
				slurmdb_pack_update_object(
					rec, msg->rpc_version, buffer);
			}
			list_iterator_destroy(itr);
		}
	} else {


		if (msg->update_list) {
			itr = list_iterator_create(msg->update_list);
			while ((rec = list_next(itr))) {
				if (rec->type > SLURMDB_MODIFY_WCKEY)
					list_remove(itr);
			}
			count = list_count(msg->update_list);
		}

		pack32(count, buffer);

		if (count) {
			list_iterator_reset(itr);
			itr = list_iterator_create(msg->update_list);
			while ((rec = list_next(itr))) {
				slurmdb_pack_update_object(
					rec, msg->rpc_version, buffer);
			}
		}
		if (itr)
			list_iterator_destroy(itr);
	}
}
