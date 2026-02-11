pio_send_control(struct hfi1_devdata *dd, int op)
{
	u64 reg, mask;
	unsigned long flags;
	int write = 1;
	int flush = 0;

	spin_lock_irqsave(&dd->sendctrl_lock, flags);

	reg = read_csr(dd, SEND_CTRL);
	switch (op) {
	case PSC_GLOBAL_ENABLE:
		reg |= SEND_CTRL_SEND_ENABLE_SMASK;

	case PSC_DATA_VL_ENABLE:

		mask = (((~0ull)<<num_vls) & SEND_CTRL_UNSUPPORTED_VL_MASK)<<
				SEND_CTRL_UNSUPPORTED_VL_SHIFT;
		reg = (reg & ~SEND_CTRL_UNSUPPORTED_VL_SMASK) | mask;
		break;
	case PSC_GLOBAL_DISABLE:
		reg &= ~SEND_CTRL_SEND_ENABLE_SMASK;
		break;
	case PSC_GLOBAL_VLARB_ENABLE:
		reg |= SEND_CTRL_VL_ARBITER_ENABLE_SMASK;
		break;
	case PSC_GLOBAL_VLARB_DISABLE:
		reg &= ~SEND_CTRL_VL_ARBITER_ENABLE_SMASK;
		break;
	case PSC_CM_RESET:
		__cm_reset(dd, reg);
		write = 0;
		break;
	case PSC_DATA_VL_DISABLE:
		reg |= SEND_CTRL_UNSUPPORTED_VL_SMASK;
		flush = 1;
		break;
	default:
		dd_dev_err(dd, "%s: invalid control %d\n", __func__, op);
		break;
	}

	if (write) {
		write_csr(dd, SEND_CTRL, reg);
		if (flush)
			(void) read_csr(dd, SEND_CTRL);
	}

	spin_unlock_irqrestore(&dd->sendctrl_lock, flags);
}
