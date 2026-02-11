s2io_txpic_intr_handle(struct s2io_nic *sp)
{
	struct XENA_dev_config __iomem *bar0 = sp->bar0;
	u64 val64;

	val64 = readq(&bar0->pic_int_status);
	if (val64 & PIC_INT_GPIO) {
		val64 = readq(&bar0->gpio_int_reg);
		if ((val64 & GPIO_INT_REG_LINK_DOWN) &&
		    (val64 & GPIO_INT_REG_LINK_UP)) {


			val64 |= GPIO_INT_REG_LINK_DOWN;
			val64 |= GPIO_INT_REG_LINK_UP;
			writeq(val64, &bar0->gpio_int_reg);
			val64 = readq(&bar0->gpio_int_mask);
			val64 &= ~(GPIO_INT_MASK_LINK_UP |
				   GPIO_INT_MASK_LINK_DOWN);
			writeq(val64, &bar0->gpio_int_mask);
		} else if (val64 & GPIO_INT_REG_LINK_UP) {
			val64 = readq(&bar0->adapter_status);

			val64 = readq(&bar0->adapter_control);
			val64 |= ADAPTER_CNTL_EN;
			writeq(val64, &bar0->adapter_control);
			val64 |= ADAPTER_LED_ON;
			writeq(val64, &bar0->adapter_control);
			if (!sp->device_enabled_once)
				sp->device_enabled_once = 1;

			s2io_link(sp, LINK_UP);


			val64 = readq(&bar0->gpio_int_mask);
			val64 &= ~GPIO_INT_MASK_LINK_DOWN;
			val64 |= GPIO_INT_MASK_LINK_UP;
			writeq(val64, &bar0->gpio_int_mask);

		} else if (val64 & GPIO_INT_REG_LINK_DOWN) {
			val64 = readq(&bar0->adapter_status);
			s2io_link(sp, LINK_DOWN);

			val64 = readq(&bar0->gpio_int_mask);
			val64 &= ~GPIO_INT_MASK_LINK_UP;
			val64 |= GPIO_INT_MASK_LINK_DOWN;
			writeq(val64, &bar0->gpio_int_mask);


			val64 = readq(&bar0->adapter_control);
			val64 = val64 & (~ADAPTER_LED_ON);
			writeq(val64, &bar0->adapter_control);
		}
	}
	val64 = readq(&bar0->gpio_int_mask);
}
