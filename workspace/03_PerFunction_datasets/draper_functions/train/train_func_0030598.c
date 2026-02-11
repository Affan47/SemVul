bttv_tea575x_set_direction(struct snd_tea575x *tea, bool output)
{
	struct bttv *btv = tea->private_data;
	struct bttv_tea575x_gpio gpio = btv->tea_gpio;
	u32 mask = (1 << gpio.clk) | (1 << gpio.wren) | (1 << gpio.data) |
		   (1 << gpio.most);

	if (output)
		gpio_inout(mask, (1 << gpio.data) | (1 << gpio.clk) |
				 (1 << gpio.wren));
	else
		gpio_inout(mask, (1 << gpio.clk) | (1 << gpio.wren));
}
