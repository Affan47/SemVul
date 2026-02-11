brasero_checksum_files_get_line_num (BraseroChecksumFiles *self,
				     BraseroVolFileHandle *handle)
{
	BraseroBurnResult result;
	int num = 0;

	while ((result = brasero_volume_file_read_line (handle, NULL, 0)) == BRASERO_BURN_RETRY)
		num ++;

	if (result == BRASERO_BURN_ERR)
		return -1;

	brasero_volume_file_rewind (handle);
	return num;
}
