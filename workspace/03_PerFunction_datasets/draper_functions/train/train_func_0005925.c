APar_ReadFile(char* destination_buffer, FILE* a_file, uint32_t bytes_to_read) {
	uint32_t bytes_read = 0;
	if (destination_buffer != NULL) {
		fseeko(a_file, 0, SEEK_SET);
		bytes_read = (uint32_t)fread(destination_buffer, 1, (size_t)bytes_to_read, a_file);
		file_size += bytes_read;
	}
	return bytes_read;
}
