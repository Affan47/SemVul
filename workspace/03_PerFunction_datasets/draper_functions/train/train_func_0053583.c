isl29018_read_proximity_ir(struct isl29018_chip *chip, int scheme,
		int *near_ir)
{
	int status;
	int prox_data = -1;
	int ir_data = -1;


	status = regmap_update_bits(chip->regmap, ISL29018_REG_ADD_COMMANDII,
			COMMANDII_SCHEME_MASK,
			scheme << COMMANDII_SCHEME_SHIFT);
	if (status) {
		dev_err(chip->dev, "Error in setting operating mode\n");
		return status;
	}

	prox_data = isl29018_read_sensor_input(chip,
					COMMMAND1_OPMODE_PROX_ONCE);
	if (prox_data < 0)
		return prox_data;

	if (scheme == 1) {
		*near_ir = prox_data;
		return 0;
	}

	ir_data = isl29018_read_sensor_input(chip, COMMMAND1_OPMODE_IR_ONCE);

	if (ir_data < 0)
		return ir_data;

	if (prox_data >= ir_data)
		*near_ir = prox_data - ir_data;
	else
		*near_ir = 0;

	return 0;
}
