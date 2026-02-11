gpio_7220_mod(struct qib_devdata *dd, u32 out, u32 dir, u32 mask)
{
	u64 read_val, new_out;
	unsigned long flags;

	if (mask) {

		dir &= mask;
		out &= mask;
		spin_lock_irqsave(&dd->cspec->gpio_lock, flags);
		dd->cspec->extctrl &= ~((u64)mask << SYM_LSB(EXTCtrl, GPIOOe));
		dd->cspec->extctrl |= ((u64) dir << SYM_LSB(EXTCtrl, GPIOOe));
		new_out = (dd->cspec->gpio_out & ~mask) | out;

		qib_write_kreg(dd, kr_extctrl, dd->cspec->extctrl);
		qib_write_kreg(dd, kr_gpio_out, new_out);
		dd->cspec->gpio_out = new_out;
		spin_unlock_irqrestore(&dd->cspec->gpio_lock, flags);
	}


	read_val = qib_read_kreg64(dd, kr_extstatus);
	return SYM_FIELD(read_val, EXTStatus, GPIOIn);
}
