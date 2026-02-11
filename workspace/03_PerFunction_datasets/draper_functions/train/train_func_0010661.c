mv_u3d_irq(int irq, void *dev)
{
	struct mv_u3d *u3d = (struct mv_u3d *)dev;
	u32 status, intr;
	u32 bridgesetting;
	u32 trbunderrun;

	spin_lock(&u3d->lock);

	status = ioread32(&u3d->vuc_regs->intrcause);
	intr = ioread32(&u3d->vuc_regs->intrenable);
	status &= intr;

	if (status == 0) {
		spin_unlock(&u3d->lock);
		dev_err(u3d->dev, "irq error!\n");
		return IRQ_NONE;
	}

	if (status & MV_U3D_USBINT_VBUS_VALID) {
		bridgesetting = ioread32(&u3d->vuc_regs->bridgesetting);
		if (bridgesetting & MV_U3D_BRIDGE_SETTING_VBUS_VALID) {

			bridgesetting = MV_U3D_BRIDGE_SETTING_VBUS_VALID;
			iowrite32(bridgesetting, &u3d->vuc_regs->bridgesetting);
			dev_dbg(u3d->dev, "vbus valid\n");

			u3d->usb_state = USB_STATE_POWERED;
			u3d->vbus_valid_detect = 0;


			if (!u3d->vbus) {
				spin_unlock(&u3d->lock);
				mv_u3d_vbus_session(&u3d->gadget, 1);
				spin_lock(&u3d->lock);
			}
		} else
			dev_err(u3d->dev, "vbus bit is not set\n");
	}


	if (status & MV_U3D_USBINT_UNDER_RUN) {
		trbunderrun = ioread32(&u3d->vuc_regs->trbunderrun);
		dev_err(u3d->dev, "under run, ep%d\n", trbunderrun);
		iowrite32(trbunderrun, &u3d->vuc_regs->trbunderrun);
		mv_u3d_irq_process_error(u3d);
	}

	if (status & (MV_U3D_USBINT_RXDESC_ERR | MV_U3D_USBINT_TXDESC_ERR)) {

		iowrite32(status & (MV_U3D_USBINT_RXDESC_ERR
			| MV_U3D_USBINT_TXDESC_ERR),
			&u3d->vuc_regs->intrcause);
		dev_err(u3d->dev, "desc err 0x%x\n", status);
		mv_u3d_irq_process_error(u3d);
	}

	if (status & MV_U3D_USBINT_LINK_CHG)
		mv_u3d_irq_process_link_change(u3d);

	if (status & MV_U3D_USBINT_TX_COMPLETE)
		mv_u3d_irq_process_tr_complete(u3d);

	if (status & MV_U3D_USBINT_RX_COMPLETE)
		mv_u3d_irq_process_tr_complete(u3d);

	if (status & MV_U3D_USBINT_SETUP)
		mv_u3d_irq_process_setup(u3d);

	spin_unlock(&u3d->lock);
	return IRQ_HANDLED;
}
