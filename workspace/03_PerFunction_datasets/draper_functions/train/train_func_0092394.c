to_reg(int gpio, enum ctrl_register reg_type)
{
	int reg;

	if (gpio == 94)
		return GPIOPANELCTL;

	if (reg_type == CTRL_IN) {
		if (gpio < 8)
			reg = GPIO0P0CTLI;
		else
			reg = GPIO1P0CTLI;
	} else {
		if (gpio < 8)
			reg = GPIO0P0CTLO;
		else
			reg = GPIO1P0CTLO;
	}

	return reg + gpio % 8;
}
