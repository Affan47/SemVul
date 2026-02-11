nct6683_setup_fans(struct nct6683_data *data)
{
	int i;
	u8 reg;

	for (i = 0; i < NCT6683_NUM_REG_FAN; i++) {
		reg = nct6683_read(data, NCT6683_REG_FANIN_CFG(i));
		if (reg & 0x80)
			data->have_fan |= 1 << i;
		data->fanin_cfg[i] = reg;
	}
	for (i = 0; i < NCT6683_NUM_REG_PWM; i++) {
		reg = nct6683_read(data, NCT6683_REG_FANOUT_CFG(i));
		if (reg & 0x80)
			data->have_pwm |= 1 << i;
		data->fanout_cfg[i] = reg;
	}
}
