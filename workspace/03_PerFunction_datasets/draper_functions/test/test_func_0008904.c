snd_es1968_tea575x_set_direction(struct snd_tea575x *tea, bool output)
{
	struct es1968 *chip = tea->private_data;
	unsigned long io = chip->io_port + GPIO_DATA;
	u16 odir = inw(io + IO_DIR);
	struct snd_es1968_tea575x_gpio gpio = *get_tea575x_gpio(chip);

	if (output) {
		outw(~((1 << gpio.data) | (1 << gpio.clk) | (1 << gpio.wren)),
			io + IO_MASK);
		outw(odir | (1 << gpio.data) | (1 << gpio.clk) | (1 << gpio.wren),
			io + IO_DIR);
	} else {
		outw(~((1 << gpio.clk) | (1 << gpio.wren) | (1 << gpio.data) | (1 << gpio.most)),
			io + IO_MASK);
		outw((odir & ~((1 << gpio.data) | (1 << gpio.most)))
			| (1 << gpio.clk) | (1 << gpio.wren), io + IO_DIR);
	}
}
