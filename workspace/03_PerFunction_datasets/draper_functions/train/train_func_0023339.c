syscon_gpio_dir_out(struct gpio_chip *chip, unsigned offset, int val)
{
	struct syscon_gpio_priv *priv = to_syscon_gpio(chip);

	if (priv->data->flags & GPIO_SYSCON_FEAT_DIR) {
		unsigned int offs;

		offs = priv->dir_reg_offset +
		       priv->data->dir_bit_offset + offset;

		regmap_update_bits(priv->syscon,
				   (offs / SYSCON_REG_BITS) * SYSCON_REG_SIZE,
				   BIT(offs % SYSCON_REG_BITS),
				   BIT(offs % SYSCON_REG_BITS));
	}

	priv->data->set(chip, offset, val);

	return 0;
}
