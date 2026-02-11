mmio_74xx_dir_out(struct gpio_chip *gc, unsigned int gpio, int val)
{
	struct mmio_74xx_gpio_priv *priv = to_74xx_gpio(gc);

	if (priv->flags & MMIO_74XX_DIR_OUT) {
		gc->set(gc, gpio, val);
		return 0;
	}

	return -ENOTSUPP;
}
