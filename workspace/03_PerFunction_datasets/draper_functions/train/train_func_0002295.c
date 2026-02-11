private_data_string(uint16_t private_data, char *str, int str_len)
{
	if (str_len > 0)
		str[0] = '\0';
	if (str_len < 55) {
		error("private_data_string: output buffer too small");
		return;
	}

	if (private_data & PRIVATE_DATA_JOBS)
		strcat(str, "jobs");
	if (private_data & PRIVATE_DATA_NODES) {
		if (str[0])
			strcat(str, ",");
		strcat(str, "nodes");
	}
	if (private_data & PRIVATE_DATA_PARTITIONS) {
		if (str[0])
			strcat(str, ",");
		strcat(str, "partitions");
	}
	if (private_data & PRIVATE_DATA_USAGE) {
		if (str[0])
			strcat(str, ",");
		strcat(str, "usage");
	}
	if (private_data & PRIVATE_DATA_USERS) {
		if (str[0])
			strcat(str, ",");
		strcat(str, "users");
	}
	if (private_data & PRIVATE_DATA_ACCOUNTS) {
		if (str[0])
			strcat(str, ",");
		strcat(str, "accounts");
	}
	if (private_data & PRIVATE_DATA_RESERVATIONS) {
		if (str[0])
			strcat(str, ",");
		strcat(str, "reservations");
	}


	if (str[0] == '\0')
		strcat(str, "none");
}
