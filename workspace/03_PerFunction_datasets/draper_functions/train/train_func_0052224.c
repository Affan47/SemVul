hpi_control_get_string(const u32 h_control, const u16 attribute,
	char *psz_string, const u32 string_length)
{
	unsigned int sub_string_index = 0, j = 0;
	char c = 0;
	unsigned int n = 0;
	u16 err = 0;

	if ((string_length < 1) || (string_length > 256))
		return HPI_ERROR_INVALID_CONTROL_VALUE;
	for (sub_string_index = 0; sub_string_index < string_length;
		sub_string_index += 8) {
		struct hpi_message hm;
		struct hpi_response hr;

		hpi_init_message_response(&hm, &hr, HPI_OBJ_CONTROL,
			HPI_CONTROL_GET_STATE);
		if (hpi_handle_indexes(h_control, &hm.adapter_index,
				&hm.obj_index))
			return HPI_ERROR_INVALID_HANDLE;
		hm.u.c.attribute = attribute;
		hm.u.c.param1 = sub_string_index;
		hm.u.c.param2 = 0;
		hpi_send_recv(&hm, &hr);

		if (sub_string_index == 0
			&& (hr.u.cu.chars8.remaining_chars + 8) >
			string_length)
			return HPI_ERROR_INVALID_CONTROL_VALUE;

		if (hr.error) {
			err = hr.error;
			break;
		}
		for (j = 0; j < 8; j++) {
			c = hr.u.cu.chars8.sz_data[j];
			psz_string[sub_string_index + j] = c;
			n++;
			if (n >= string_length) {
				psz_string[string_length - 1] = 0;
				err = HPI_ERROR_INVALID_CONTROL_VALUE;
				break;
			}
			if (c == 0)
				break;
		}

		if ((hr.u.cu.chars8.remaining_chars == 0)
			&& ((sub_string_index + j) < string_length)
			&& (c != 0)) {
			c = 0;
			psz_string[sub_string_index + j] = c;
		}
		if (c == 0)
			break;
	}
	return err;
}
