init_pci_device_addresses(struct pm8001_hba_info *pm8001_ha)
{
	void __iomem *base_addr;
	u32	value;
	u32	offset;
	u32	pcibar;
	u32	pcilogic;

	value = pm8001_cr32(pm8001_ha, 0, MSGU_SCRATCH_PAD_0);
	offset = value & 0x03FFFFFF;

	PM8001_INIT_DBG(pm8001_ha,
		pm8001_printk("Scratchpad 0 Offset: 0x%x value 0x%x\n",
				offset, value));
	pcilogic = (value & 0xFC000000) >> 26;
	pcibar = get_pci_bar_index(pcilogic);
	PM8001_INIT_DBG(pm8001_ha,
		pm8001_printk("Scratchpad 0 PCI BAR: %d\n", pcibar));
	pm8001_ha->main_cfg_tbl_addr = base_addr =
		pm8001_ha->io_mem[pcibar].memvirtaddr + offset;
	pm8001_ha->general_stat_tbl_addr =
		base_addr + (pm8001_cr32(pm8001_ha, pcibar, offset + 0x18) &
					0xFFFFFF);
	pm8001_ha->inbnd_q_tbl_addr =
		base_addr + (pm8001_cr32(pm8001_ha, pcibar, offset + 0x1C) &
					0xFFFFFF);
	pm8001_ha->outbnd_q_tbl_addr =
		base_addr + (pm8001_cr32(pm8001_ha, pcibar, offset + 0x20) &
					0xFFFFFF);
	pm8001_ha->ivt_tbl_addr =
		base_addr + (pm8001_cr32(pm8001_ha, pcibar, offset + 0x8C) &
					0xFFFFFF);
	pm8001_ha->pspa_q_tbl_addr =
		base_addr + (pm8001_cr32(pm8001_ha, pcibar, offset + 0x90) &
					0xFFFFFF);
	pm8001_ha->fatal_tbl_addr =
		base_addr + (pm8001_cr32(pm8001_ha, pcibar, offset + 0xA0) &
					0xFFFFFF);

	PM8001_INIT_DBG(pm8001_ha,
			pm8001_printk("GST OFFSET 0x%x\n",
			pm8001_cr32(pm8001_ha, pcibar, offset + 0x18)));
	PM8001_INIT_DBG(pm8001_ha,
			pm8001_printk("INBND OFFSET 0x%x\n",
			pm8001_cr32(pm8001_ha, pcibar, offset + 0x1C)));
	PM8001_INIT_DBG(pm8001_ha,
			pm8001_printk("OBND OFFSET 0x%x\n",
			pm8001_cr32(pm8001_ha, pcibar, offset + 0x20)));
	PM8001_INIT_DBG(pm8001_ha,
			pm8001_printk("IVT OFFSET 0x%x\n",
			pm8001_cr32(pm8001_ha, pcibar, offset + 0x8C)));
	PM8001_INIT_DBG(pm8001_ha,
			pm8001_printk("PSPA OFFSET 0x%x\n",
			pm8001_cr32(pm8001_ha, pcibar, offset + 0x90)));
	PM8001_INIT_DBG(pm8001_ha,
			pm8001_printk("addr - main cfg %p general status %p\n",
			pm8001_ha->main_cfg_tbl_addr,
			pm8001_ha->general_stat_tbl_addr));
	PM8001_INIT_DBG(pm8001_ha,
			pm8001_printk("addr - inbnd %p obnd %p\n",
			pm8001_ha->inbnd_q_tbl_addr,
			pm8001_ha->outbnd_q_tbl_addr));
	PM8001_INIT_DBG(pm8001_ha,
			pm8001_printk("addr - pspa %p ivt %p\n",
			pm8001_ha->pspa_q_tbl_addr,
			pm8001_ha->ivt_tbl_addr));
}
