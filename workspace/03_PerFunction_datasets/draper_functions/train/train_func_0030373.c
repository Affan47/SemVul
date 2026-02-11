adv7182_init(struct adv7180_state *state)
{
	if (state->chip_info->flags & ADV7180_FLAG_MIPI_CSI2)
		adv7180_write(state, ADV7180_REG_CSI_SLAVE_ADDR,
			ADV7180_DEFAULT_CSI_I2C_ADDR << 1);

	if (state->chip_info->flags & ADV7180_FLAG_I2P)
		adv7180_write(state, ADV7180_REG_VPP_SLAVE_ADDR,
			ADV7180_DEFAULT_VPP_I2C_ADDR << 1);

	if (state->chip_info->flags & ADV7180_FLAG_V2) {

		adv7180_write(state, 0x0080, 0x51);
		adv7180_write(state, 0x0081, 0x51);
		adv7180_write(state, 0x0082, 0x68);
	}


	if (state->chip_info->flags & ADV7180_FLAG_MIPI_CSI2) {
		adv7180_write(state, 0x0003, 0x4e);
		adv7180_write(state, 0x0004, 0x57);
		adv7180_write(state, 0x001d, 0xc0);
	} else {
		if (state->chip_info->flags & ADV7180_FLAG_V2)
			adv7180_write(state, 0x0004, 0x17);
		else
			adv7180_write(state, 0x0004, 0x07);
		adv7180_write(state, 0x0003, 0x0c);
		adv7180_write(state, 0x001d, 0x40);
	}

	adv7180_write(state, 0x0013, 0x00);

	return 0;
}
