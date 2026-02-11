liblo10k1lf_can_load_file(FILE *file, unsigned int ft)
{
	liblo10k1_file_header_t fhdr;
	liblo10k1_file_part_info_t file_info;
	int err;

	if (fread(&fhdr, sizeof(liblo10k1_file_header_t), 1, file) != 1)
		return LD10K1_LF_ERR_READ;


	if (strcmp(fhdr.signature, LD10K1_FILE_SIGNATURE) != 0)
		return LD10K1_LF_ERR_SIGNATURE;


	if ((err = liblo10k1lf_find_load_part_ws(file, LD10K1_FP_INFO, sizeof(file_info), &file_info)) < 0)
		return err;

	if (file_info.minimal_reader_version_major > CREATER_MAJOR)
		return LD10K1_LF_ERR_VERSION;

	if (file_info.minimal_reader_version_major == CREATER_MAJOR &&
		file_info.minimal_reader_version_minor > CREATER_MINOR)
		return LD10K1_LF_ERR_VERSION;

	if (file_info.minimal_reader_version_major == CREATER_MAJOR &&
		file_info.minimal_reader_version_minor == CREATER_MINOR &&
		file_info.minimal_reader_version_subminor > CREATER_SUBMINOR)
		return LD10K1_LF_ERR_VERSION;


	if (file_info.file_type != ft)
		return LD10K1_LF_ERR_FILE_TYPE;

	return 0;
}
