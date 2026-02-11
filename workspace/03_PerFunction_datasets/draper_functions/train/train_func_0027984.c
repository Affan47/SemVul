i2c_pca_pf_handler(int this_irq, void *dev_id)
{
	struct i2c_pca_pf_data *i2c = dev_id;

	if ((i2c->algo_data.read_byte(i2c, I2C_PCA_CON) & I2C_PCA_CON_SI) == 0)
		return IRQ_NONE;

	wake_up(&i2c->wait);

	return IRQ_HANDLED;
}
