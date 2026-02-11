mac_get_cam_mask(struct mac_regs __iomem *regs, u8 *mask)
{
	int i;


	BYTE_REG_BITS_SET(CAMCR_PS_CAM_MASK, CAMCR_PS1 | CAMCR_PS0, &regs->CAMCR);

	writeb(0, &regs->CAMADDR);


	for (i = 0; i < 8; i++)
		*mask++ = readb(&(regs->MARCAM[i]));


	writeb(0, &regs->CAMADDR);


	BYTE_REG_BITS_SET(CAMCR_PS_MAR, CAMCR_PS1 | CAMCR_PS0, &regs->CAMCR);
}
