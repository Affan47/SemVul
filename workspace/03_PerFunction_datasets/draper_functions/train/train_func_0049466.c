slic_mcast_set_mask(struct adapter *adapter)
{
	__iomem struct slic_regs *slic_regs = adapter->slic_regs;

	if (adapter->macopts & (MAC_ALLMCAST | MAC_PROMISC)) {


		slic_reg32_write(&slic_regs->slic_mcastlow, 0xFFFFFFFF, FLUSH);
		slic_reg32_write(&slic_regs->slic_mcasthigh, 0xFFFFFFFF,
				 FLUSH);
	} else {


		slic_reg32_write(&slic_regs->slic_mcastlow,
			(u32)(adapter->mcastmask & 0xFFFFFFFF), FLUSH);
		slic_reg32_write(&slic_regs->slic_mcasthigh,
			(u32)((adapter->mcastmask >> 32) & 0xFFFFFFFF), FLUSH);
	}
}
