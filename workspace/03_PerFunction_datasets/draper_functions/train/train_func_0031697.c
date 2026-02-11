cmvs_file_name(struct uea_softc *sc, char *const cmv_name, int ver)
{
	char file_arr[] = "CMVxy.bin";
	char *file;

	kernel_param_lock(THIS_MODULE);

	if (cmv_file[sc->modem_index] == NULL) {
		if (UEA_CHIP_VERSION(sc) == ADI930)
			file_arr[3] = '9';
		else if (UEA_CHIP_VERSION(sc) == EAGLE_IV)
			file_arr[3] = '4';
		else
			file_arr[3] = 'e';

		file_arr[4] = IS_ISDN(sc) ? 'i' : 'p';
		file = file_arr;
	} else
		file = cmv_file[sc->modem_index];

	strcpy(cmv_name, FW_DIR);
	strlcat(cmv_name, file, UEA_FW_NAME_MAX);
	if (ver == 2)
		strlcat(cmv_name, ".v2", UEA_FW_NAME_MAX);
	kernel_param_unlock(THIS_MODULE);
}
