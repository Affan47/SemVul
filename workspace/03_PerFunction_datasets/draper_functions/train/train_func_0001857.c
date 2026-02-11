nm_setting_bond_get_valid_options  (NMSettingBond *setting)
{
	static const char *array[G_N_ELEMENTS (defaults) + 1] = { NULL };
	int i;


	if (G_UNLIKELY (array[0] == NULL)) {
		for (i = 0; i < G_N_ELEMENTS (defaults); i++)
			array[i] = defaults[i].opt;
		array[i] = NULL;
	}
	return array;
}
