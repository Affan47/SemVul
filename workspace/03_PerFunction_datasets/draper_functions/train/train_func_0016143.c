adnp_irq_bus_unlock(struct irq_data *d)
{
	struct gpio_chip *gc = irq_data_get_irq_chip_data(d);
	struct adnp *adnp = to_adnp(gc);
	unsigned int num_regs = 1 << adnp->reg_shift, i;

	mutex_lock(&adnp->i2c_lock);

	for (i = 0; i < num_regs; i++)
		adnp_write(adnp, GPIO_IER(adnp) + i, adnp->irq_enable[i]);

	mutex_unlock(&adnp->i2c_lock);
	mutex_unlock(&adnp->irq_lock);
}
