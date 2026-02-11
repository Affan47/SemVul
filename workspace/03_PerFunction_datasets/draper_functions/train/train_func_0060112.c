_unpack_accounting_update_msg(accounting_update_msg_t **msg,
					 Buf buffer,
					 uint16_t protocol_version)
{
	uint32_t count = 0;
	int i = 0;
	accounting_update_msg_t *msg_ptr =
		xmalloc(sizeof(accounting_update_msg_t));
	slurmdb_update_object_t *rec = NULL;

	*msg = msg_ptr;

	if (protocol_version >= SLURM_2_3_PROTOCOL_VERSION) {
		safe_unpack16(&msg_ptr->rpc_version, buffer);
		safe_unpack32(&count, buffer);
		msg_ptr->update_list = list_create(
			slurmdb_destroy_update_object);
		for (i=0; i<count; i++) {
			if ((slurmdb_unpack_update_object(
				    &rec, msg_ptr->rpc_version, buffer))
			   == SLURM_ERROR)
				goto unpack_error;
			list_append(msg_ptr->update_list, rec);
		}
	} else {
		error("_unpack_accounting_update_msg: protocol_version "
		      "%hu not supported", protocol_version);
		goto unpack_error;
	}
	return SLURM_SUCCESS;

unpack_error:
	slurm_free_accounting_update_msg(msg_ptr);
	*msg = NULL;
	return SLURM_ERROR;
}
