mv_u3d_controller_start(struct mv_u3d *u3d)
{
	u32 usbintr;
	u32 temp;


	temp = ioread32(&u3d->vuc_regs->ltssm);
	temp |= MV_U3D_LTSSM_PHY_INIT_DONE;
	iowrite32(temp, &u3d->vuc_regs->ltssm);


	usbintr = MV_U3D_INTR_ENABLE_LINK_CHG | MV_U3D_INTR_ENABLE_TXDESC_ERR |
		MV_U3D_INTR_ENABLE_RXDESC_ERR | MV_U3D_INTR_ENABLE_TX_COMPLETE |
		MV_U3D_INTR_ENABLE_RX_COMPLETE | MV_U3D_INTR_ENABLE_SETUP |
		(u3d->vbus_valid_detect ? MV_U3D_INTR_ENABLE_VBUS_VALID : 0);
	iowrite32(usbintr, &u3d->vuc_regs->intrenable);


	iowrite32(0x1, &u3d->vuc_regs->ctrlepenable);


	iowrite32(MV_U3D_CMD_RUN_STOP, &u3d->op_regs->usbcmd);
	dev_dbg(u3d->dev, "after u3d_start, USBCMD 0x%x\n",
		ioread32(&u3d->op_regs->usbcmd));
}
