pca953x_gpio_get_value(struct gpio_chip *gc, unsigned off)
{
	struct pca953x_chip *chip = to_pca(gc);
	u32 reg_val;
	int ret, offset = 0;

	mutex_lock(&chip->i2c_lock);
	switch (chip->chip_type) {
	case PCA953X_TYPE:
		offset = PCA953X_INPUT;
		break;
	case PCA957X_TYPE:
		offset = PCA957X_IN;
		break;
	}
	ret = pca953x_read_single(chip, offset, &reg_val, off);
	mutex_unlock(&chip->i2c_lock);
	if (ret < 0) {


		return 0;
	}

	return (reg_val & (1u << (off % BANK_SZ))) ? 1 : 0;
}
