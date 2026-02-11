omapi_connection_write_typed_data (omapi_object_t *c,
						omapi_typed_data_t *data)
{
	isc_result_t status;
	omapi_handle_t handle;


	if (!data)
		return omapi_connection_put_uint32 (c, 0);

	switch (data -> type) {
	      case omapi_datatype_int:
		status = omapi_connection_put_uint32 (c, sizeof (u_int32_t));
		if (status != ISC_R_SUCCESS)
			return status;
		return omapi_connection_put_uint32 (c, ((u_int32_t)
							(data -> u.integer)));

	      case omapi_datatype_string:
	      case omapi_datatype_data:
		status = omapi_connection_put_uint32 (c, data -> u.buffer.len);
		if (status != ISC_R_SUCCESS)
			return status;
		if (data -> u.buffer.len)
			return omapi_connection_copyin
				(c, data -> u.buffer.value,
				 data -> u.buffer.len);
		return ISC_R_SUCCESS;

	      case omapi_datatype_object:
		if (data -> u.object) {
			status = omapi_object_handle (&handle,
						      data -> u.object);
			if (status != ISC_R_SUCCESS)
				return status;
		} else
			handle = 0;
		status = omapi_connection_put_uint32 (c, sizeof handle);
		if (status != ISC_R_SUCCESS)
			return status;
		return omapi_connection_put_uint32 (c, handle);

	}
	return DHCP_R_INVALIDARG;
}
