mv_u3d_ep_set_stall(struct mv_u3d *u3d, u8 ep_num, u8 direction, int stall)
{
	u32 tmp;
	struct mv_u3d_ep *ep = u3d->eps;

	dev_dbg(u3d->dev, "%s\n", __func__);
	if (direction == MV_U3D_EP_DIR_OUT) {
		tmp = ioread32(&u3d->vuc_regs->epcr[ep->ep_num].epxoutcr0);
		if (stall)
			tmp |= MV_U3D_EPXCR_EP_HALT;
		else
			tmp &= ~MV_U3D_EPXCR_EP_HALT;
		iowrite32(tmp, &u3d->vuc_regs->epcr[ep->ep_num].epxoutcr0);
	} else {
		tmp = ioread32(&u3d->vuc_regs->epcr[ep->ep_num].epxincr0);
		if (stall)
			tmp |= MV_U3D_EPXCR_EP_HALT;
		else
			tmp &= ~MV_U3D_EPXCR_EP_HALT;
		iowrite32(tmp, &u3d->vuc_regs->epcr[ep->ep_num].epxincr0);
	}
}
