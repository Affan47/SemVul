init_hwif_hpt366(ide_hwif_t *hwif)
{
	struct hpt_info *info	= hpt3xx_get_info(hwif->dev);
	u8  chip_type		= info->chip_type;


	hwif->select_data	= hwif->channel ? 0x54 : 0x50;


	if (chip_type >= HPT372N && info->dpll_clk && info->pci_clk < 66) {


		hwif->host->host_flags |= IDE_HFLAG_SERIALIZE;
		hwif->rw_disk = &hpt3xxn_rw_disk;
	}
}
