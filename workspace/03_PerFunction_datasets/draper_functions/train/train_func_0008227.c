omapi_protocol_set_value (omapi_object_t *h,
				       omapi_object_t *id,
				       omapi_data_string_t *name,
				       omapi_typed_data_t *value)
{
	omapi_protocol_object_t *p;
	omapi_remote_auth_t *r;

	if (h -> type != omapi_type_protocol)
		return DHCP_R_INVALIDARG;
	p = (omapi_protocol_object_t *)h;

	if (omapi_ds_strcmp (name, "default-authenticator") == 0) {
		if (value -> type != omapi_datatype_object)
			return DHCP_R_INVALIDARG;

		if (!value || !value -> u.object) {
			p -> default_auth = (omapi_remote_auth_t *)0;
		} else {
			for (r = p -> remote_auth_list; r; r = r -> next)
				if (r -> a == value -> u.object)
					break;

			if (!r)
				return DHCP_R_KEY_UNKNOWN;

			p -> default_auth = r;
		}

		return ISC_R_SUCCESS;
	}

	if (h -> inner && h -> inner -> type -> set_value)
		return (*(h -> inner -> type -> set_value))
			(h -> inner, id, name, value);
	return ISC_R_NOTFOUND;
}
