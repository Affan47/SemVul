act8865_get_init_data(int id, struct act8865_platform_data *pdata)
{
	int i;

	if (!pdata)
		return NULL;

	for (i = 0; i < pdata->num_regulators; i++) {
		if (pdata->regulators[i].id == id)
			return pdata->regulators[i].platform_data;
	}

	return NULL;
}
