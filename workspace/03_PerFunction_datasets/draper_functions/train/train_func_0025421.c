pch_gpio_handler(int irq, void *dev_id)
{
	struct pch_gpio *chip = dev_id;
	u32 reg_val = ioread32(&chip->reg->istatus);
	int i, ret = IRQ_NONE;

	for (i = 0; i < gpio_pins[chip->ioh]; i++) {
		if (reg_val & BIT(i)) {
			dev_dbg(chip->dev, "%s:[%d]:irq=%d  status=0x%x\n",
				__func__, i, irq, reg_val);
			generic_handle_irq(chip->irq_base + i);
			ret = IRQ_HANDLED;
		}
	}
	return ret;
}
