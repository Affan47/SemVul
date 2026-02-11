isp116x_irq(struct usb_hcd *hcd)
{
	struct isp116x *isp116x = hcd_to_isp116x(hcd);
	u16 irqstat;
	irqreturn_t ret = IRQ_NONE;

	spin_lock(&isp116x->lock);
	isp116x_write_reg16(isp116x, HCuPINTENB, 0);
	irqstat = isp116x_read_reg16(isp116x, HCuPINT);
	isp116x_write_reg16(isp116x, HCuPINT, irqstat);

	if (irqstat & (HCuPINT_ATL | HCuPINT_SOF)) {
		ret = IRQ_HANDLED;
		finish_atl_transfers(isp116x);
	}

	if (irqstat & HCuPINT_OPR) {
		u32 intstat = isp116x_read_reg32(isp116x, HCINTSTAT);
		isp116x_write_reg32(isp116x, HCINTSTAT, intstat);
		if (intstat & HCINT_UE) {
			ERR("Unrecoverable error, HC is dead!\n");


			hcd->state = HC_STATE_HALT;
			usb_hc_died(hcd);
			ret = IRQ_HANDLED;
			goto done;
		}
		if (intstat & HCINT_RHSC)


			mod_timer(&hcd->rh_timer, jiffies
				  + msecs_to_jiffies(20) + 1);
		if (intstat & HCINT_RD) {
			DBG("---- remote wakeup\n");
			usb_hcd_resume_root_hub(hcd);
		}
		irqstat &= ~HCuPINT_OPR;
		ret = IRQ_HANDLED;
	}

	if (irqstat & (HCuPINT_ATL | HCuPINT_SOF)) {
		start_atl_transfers(isp116x);
	}

	isp116x_write_reg16(isp116x, HCuPINTENB, isp116x->irqenb);
      done:
	spin_unlock(&isp116x->lock);
	return ret;
}
