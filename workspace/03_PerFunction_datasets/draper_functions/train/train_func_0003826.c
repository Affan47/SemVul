dhc6_check_status(isc_result_t rval, struct option_state *options,
		  const char *scope, unsigned *code)
{
	struct data_string msg;
	isc_result_t status;

	if ((scope == NULL) || (code == NULL))
		return DHCP_R_INVALIDARG;


	*code = STATUS_Success;


	if (options != NULL) {
		memset(&msg, 0, sizeof(msg));
		status = dhc6_get_status_code(options, code, &msg);

		if (status == ISC_R_SUCCESS) {
			status_log(*code, scope, (char *)msg.data, msg.len);
			data_string_forget(&msg, MDL);

			if (*code != STATUS_Success)
				rval = ISC_R_FAILURE;

		} else if (status != ISC_R_NOTFOUND)
			rval = status;
	}

	return rval;
}
