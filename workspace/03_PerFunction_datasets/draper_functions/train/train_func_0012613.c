error_get(void)
{

	while (error_desc_buffer[0] && isspace(error_desc_buffer[strlen(error_desc_buffer)-1]))
		error_desc_buffer[strlen(error_desc_buffer)-1] = 0;
	return error_desc_buffer;
}
