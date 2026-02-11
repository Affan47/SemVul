mcam_ctlr_power_down(struct mcam_camera *cam)
{
	unsigned long flags;

	spin_lock_irqsave(&cam->dev_lock, flags);


	mcam_reg_set_bit(cam, REG_CTRL1, C1_PWRDWN);
	cam->plat_power_down(cam);
	spin_unlock_irqrestore(&cam->dev_lock, flags);
}
