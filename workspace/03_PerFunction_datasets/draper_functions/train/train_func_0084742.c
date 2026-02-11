velocity_init_cam_filter(struct velocity_info *vptr)
{
	struct mac_regs __iomem *regs = vptr->mac_regs;
	unsigned int vid, i = 0;


	WORD_REG_BITS_SET(MCFG_PQEN, MCFG_RTGOPT, &regs->MCFG);
	WORD_REG_BITS_ON(MCFG_VIDFR, &regs->MCFG);


	memset(vptr->vCAMmask, 0, sizeof(u8) * 8);
	memset(vptr->mCAMmask, 0, sizeof(u8) * 8);
	mac_set_vlan_cam_mask(regs, vptr->vCAMmask);
	mac_set_cam_mask(regs, vptr->mCAMmask);


	for_each_set_bit(vid, vptr->active_vlans, VLAN_N_VID) {
		mac_set_vlan_cam(regs, i, (u8 *) &vid);
		vptr->vCAMmask[i / 8] |= 0x1 << (i % 8);
		if (++i >= VCAM_SIZE)
			break;
	}
	mac_set_vlan_cam_mask(regs, vptr->vCAMmask);
}
