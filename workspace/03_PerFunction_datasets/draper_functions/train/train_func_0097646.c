genwqe_info_show(struct seq_file *s, void *unused)
{
	struct genwqe_dev *cd = s->private;
	u16 val16, type;
	u64 app_id, slu_id, bitstream = -1;
	struct pci_dev *pci_dev = cd->pci_dev;

	slu_id = __genwqe_readq(cd, IO_SLU_UNITCFG);
	app_id = __genwqe_readq(cd, IO_APP_UNITCFG);

	if (genwqe_is_privileged(cd))
		bitstream = __genwqe_readq(cd, IO_SLU_BITSTREAM);

	val16 = (u16)(slu_id & 0x0fLLU);
	type  = (u16)((slu_id >> 20) & 0xffLLU);

	seq_printf(s, "%s driver version: %s\n"
		   "    Device Name/Type: %s %s CardIdx: %d\n"
		   "    SLU/APP Config  : 0x%016llx/0x%016llx\n"
		   "    Build Date      : %u/%x/%u\n"
		   "    Base Clock      : %u MHz\n"
		   "    Arch/SVN Release: %u/%llx\n"
		   "    Bitstream       : %llx\n",
		   GENWQE_DEVNAME, DRV_VERSION, dev_name(&pci_dev->dev),
		   genwqe_is_privileged(cd) ?
		   "Physical" : "Virtual or no SR-IOV",
		   cd->card_idx, slu_id, app_id,
		   (u16)((slu_id >> 12) & 0x0fLLU),
		   (u16)((slu_id >>  4) & 0xffLLU),
		   (u16)((slu_id >> 16) & 0x0fLLU) + 2010,
		   genwqe_base_clock_frequency(cd),
		   (u16)((slu_id >> 32) & 0xffLLU), slu_id >> 40,
		   bitstream);

	return 0;
}
