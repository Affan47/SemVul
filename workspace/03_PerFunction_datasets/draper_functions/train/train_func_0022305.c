dns_rbt_zero_header(FILE *file) {


	char buffer[HEADER_LENGTH];
	isc_result_t result;

	memset(buffer, 0, HEADER_LENGTH);
	result = isc_stdio_write(buffer, 1, HEADER_LENGTH, file, NULL);
	if (result != ISC_R_SUCCESS)
		return (result);

	result = fflush(file);
	if (result != ISC_R_SUCCESS)
		return (result);

	return (ISC_R_SUCCESS);
}
