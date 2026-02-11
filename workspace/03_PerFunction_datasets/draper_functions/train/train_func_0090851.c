sym_lookup_chip_table (u_short device_id, u_char revision)
{
	struct	sym_chip *chip;
	int	i;

	for (i = 0; i < sym_num_devs; i++) {
		chip = &sym_dev_table[i];
		if (device_id != chip->device_id)
			continue;
		if (revision > chip->revision_id)
			continue;
		return chip;
	}

	return NULL;
}
