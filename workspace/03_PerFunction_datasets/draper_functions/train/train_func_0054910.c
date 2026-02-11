check_requested_operating_mode(
		const enum peripheral_operation_mode requested_operation_mode,
		const enum peripheral_operation_mode valid_operating_modes[],
		portBASE_TYPE num_valid_operating_modes)
{
	bool return_value = false;
	portBASE_TYPE index_position;

	for (index_position = 0; index_position < num_valid_operating_modes;
			index_position++) {
		if (requested_operation_mode ==
				valid_operating_modes[index_position]) {
			return_value = true;
			break;
		}
	}

	return return_value;
}
