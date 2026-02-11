mac_set_vlan_cam(struct mac_regs __iomem *regs, int idx,
			     const u8 *addr)
{


	BYTE_REG_BITS_SET(CAMCR_PS_CAM_DATA, CAMCR_PS1 | CAMCR_PS0, &regs->CAMCR);

	idx &= (64 - 1);

	writeb(CAMADDR_CAMEN | CAMADDR_VCAMSL | idx, &regs->CAMADDR);
	writew(*((u16 *) addr), &regs->MARCAM[0]);

	BYTE_REG_BITS_ON(CAMCR_CAMWR, &regs->CAMCR);

	udelay(10);

	writeb(0, &regs->CAMADDR);


	BYTE_REG_BITS_SET(CAMCR_PS_MAR, CAMCR_PS1 | CAMCR_PS0, &regs->CAMCR);
}
