liblo10k1lf_load_dsp_config(liblo10k1_file_dsp_setup_t **c, char *file_name, liblo10k1_file_info_t **fi)
{
	FILE *file = NULL;
	int err;

	liblo10k1_file_info_t *i = NULL;

	file = fopen(file_name, "r");
	if (!file)
		return LD10K1_LF_ERR_OPEN;

	if ((err = liblo10k1lf_can_load_file(file, LD10K1_FP_INFO_FILE_TYPE_DSP_SETUP)) < 0)
		goto err;

	if ((err =  liblo10k1lf_load_file_info(file, &i)) < 0)
		goto err;

	if ((err =  liblo10k1lf_load_dsp_setup(c, file)) < 0)
		goto err;

	*fi = i;
	fclose(file);
	return 0;
err:
	if (i)
		liblo10k1lf_file_info_free(i);
	fclose(file);
	return err;
}
