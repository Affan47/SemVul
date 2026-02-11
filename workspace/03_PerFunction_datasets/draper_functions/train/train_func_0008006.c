dhcpctl_set_boolean_value (dhcpctl_handle h, int value,
					  const char *value_name)
{
	isc_result_t status;
	omapi_typed_data_t *tv = (omapi_typed_data_t *)0;
	omapi_data_string_t *name = (omapi_data_string_t *)0;

	status = omapi_data_string_new (&name, strlen (value_name), MDL);
	if (status != ISC_R_SUCCESS)
		return status;
	memcpy (name -> value, value_name, strlen (value_name));

	status = omapi_typed_data_new (MDL, &tv, omapi_datatype_int, value);
	if (status != ISC_R_SUCCESS) {
		omapi_data_string_dereference (&name, MDL);
		return status;
	}

	status = omapi_set_value (h, (omapi_object_t *)0, name, tv);
	omapi_data_string_dereference (&name, MDL);
	omapi_typed_data_dereference (&tv, MDL);
	return status;
}
