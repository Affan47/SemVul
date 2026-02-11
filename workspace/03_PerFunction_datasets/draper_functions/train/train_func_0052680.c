pm860x_irq(int irq, void *data)
{
	struct pm860x_chip *chip = data;
	struct pm860x_irq_data *irq_data;
	struct i2c_client *i2c;
	int read_reg = -1, value = 0;
	int i;

	i2c = (chip->id == CHIP_PM8607) ? chip->client : chip->companion;
	for (i = 0; i < ARRAY_SIZE(pm860x_irqs); i++) {
		irq_data = &pm860x_irqs[i];
		if (read_reg != irq_data->reg) {
			read_reg = irq_data->reg;
			value = pm860x_reg_read(i2c, irq_data->reg);
		}
		if (value & irq_data->enable)
			handle_nested_irq(chip->irq_base + i);
	}
	return IRQ_HANDLED;
}
