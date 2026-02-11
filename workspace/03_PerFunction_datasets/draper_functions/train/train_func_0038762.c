dhcp_group_remove (omapi_object_t *lp,
				omapi_object_t *id)
{
	struct group_object *group;
	isc_result_t status;
	if (lp -> type != dhcp_type_group)
		return DHCP_R_INVALIDARG;
	group = (struct group_object *)lp;

	group -> flags |= GROUP_OBJECT_DELETED;
	if (group_write_hook) {
		if (!(*group_write_hook) (group))
			return ISC_R_IOERROR;
	}

	status = dhcp_group_destroy ((omapi_object_t *)group, MDL);

	return status;
}
