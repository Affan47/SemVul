asihpi_tuner_band_query(struct snd_kcontrol *kcontrol,
					u16 *band_list, u32 len) {
	u32 h_control = kcontrol->private_value;
	u16 err = 0;
	u32 i;

	for (i = 0; i < len; i++) {
		err = hpi_tuner_query_band(
				h_control, i, &band_list[i]);
		if (err != 0)
			break;
	}

	if (err && (err != HPI_ERROR_INVALID_OBJ_INDEX))
		return -EIO;

	return i;
}
