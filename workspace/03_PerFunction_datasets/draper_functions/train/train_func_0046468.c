dhcp_subclass_stuff_values (omapi_object_t *c,
					 omapi_object_t *id,
					 omapi_object_t *h)
{
	struct class *subclass;
	isc_result_t status;

	if (h -> type != dhcp_type_class)
		return DHCP_R_INVALIDARG;
	subclass = (struct class *)h;
	if (subclass -> name != 0)
		return DHCP_R_INVALIDARG;


	if (h -> inner && h -> inner -> type -> stuff_values) {
		status = ((*(h -> inner -> type -> stuff_values))
			  (c, id, h -> inner));
		if (status == ISC_R_SUCCESS)
			return status;
	}

	return ISC_R_SUCCESS;
}
