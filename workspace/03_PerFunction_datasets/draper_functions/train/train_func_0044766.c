_unpack_assoc_shares_object(void **object, Buf buffer,
				       uint16_t protocol_version)
{
	uint32_t uint32_tmp;
	association_shares_object_t *object_ptr =
		xmalloc(sizeof(association_shares_object_t));

	*object = (void *) object_ptr;

	if (protocol_version >= SLURM_2_5_PROTOCOL_VERSION) {
		safe_unpack32(&object_ptr->assoc_id, buffer);

		safe_unpackstr_xmalloc(&object_ptr->cluster,
				       &uint32_tmp, buffer);
		safe_unpackstr_xmalloc(&object_ptr->name, &uint32_tmp, buffer);
		safe_unpackstr_xmalloc(&object_ptr->parent,
				       &uint32_tmp, buffer);

		safe_unpackdouble(&object_ptr->shares_norm, buffer);
		safe_unpack32(&object_ptr->shares_raw, buffer);

		safe_unpackdouble(&object_ptr->usage_efctv, buffer);
		safe_unpackdouble(&object_ptr->usage_norm, buffer);
		safe_unpack64(&object_ptr->usage_raw, buffer);

		safe_unpack64(&object_ptr->grp_cpu_mins, buffer);
		safe_unpack64(&object_ptr->cpu_run_mins, buffer);

		safe_unpack16(&object_ptr->user, buffer);
	} else {
		error("_unpack_assoc_shares_object: protocol_version "
		      "%hu not supported", protocol_version);
		goto unpack_error;
	}
	return SLURM_SUCCESS;

unpack_error:
	slurm_destroy_association_shares_object(object_ptr);
	*object = NULL;
	return SLURM_ERROR;
}
