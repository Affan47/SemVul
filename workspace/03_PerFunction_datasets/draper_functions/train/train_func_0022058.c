nct6683_setup_sensors(struct nct6683_data *data)
{
	u8 reg;
	int i;

	data->temp_num = 0;
	data->in_num = 0;
	for (i = 0; i < NCT6683_NUM_REG_MON; i++) {
		reg = nct6683_read(data, NCT6683_REG_MON_CFG(i)) & 0x7f;

		if (reg >= NUM_MON_LABELS)
			continue;

		if (nct6683_mon_label[reg] == NULL)
			continue;
		if (reg < MON_VOLTAGE_START) {
			data->temp_index[data->temp_num] = i;
			data->temp_src[data->temp_num] = reg;
			data->temp_num++;
		} else {
			data->in_index[data->in_num] = i;
			data->in_src[data->in_num] = reg;
			data->in_num++;
		}
	}
}
