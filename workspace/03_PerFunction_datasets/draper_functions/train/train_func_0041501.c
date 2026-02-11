liblo10k1lf_load_file_info(FILE *file, liblo10k1_file_info_t **fi)
{
	int err;

	liblo10k1_file_info_t *i = liblo10k1lf_file_info_alloc();

	if (!i)
		return LD10K1_ERR_NO_MEM;

	if ((err = liblo10k1lf_load_string_info(file, LD10K1_FP_FILE_INFO_NAME, &(i->name))) < 0)
		goto err;
	if ((err = liblo10k1lf_load_string_info(file, LD10K1_FP_FILE_INFO_DESC, &(i->desc))) < 0)
		goto err;
	if ((err = liblo10k1lf_load_string_info(file, LD10K1_FP_FILE_INFO_CREATER, &(i->creater))) < 0)
		goto err;
	if ((err = liblo10k1lf_load_string_info(file, LD10K1_FP_FILE_INFO_AUTHOR, &(i->author))) < 0)
		goto err;
	if ((err = liblo10k1lf_load_string_info(file, LD10K1_FP_FILE_INFO_COPYRIGHT, &(i->copyright))) < 0)
		goto err;
	if ((err = liblo10k1lf_load_string_info(file, LD10K1_FP_FILE_INFO_LICENCE, &(i->license))) < 0)
		goto err;

	*fi = i;
	return 0;
err:
	if (i)
		liblo10k1lf_file_info_free(i);
	return err;
}
