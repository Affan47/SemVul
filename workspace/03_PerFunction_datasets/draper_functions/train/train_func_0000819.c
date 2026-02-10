pdcnew_cable_detect(ide_hwif_t *hwif)
{
	if (get_indexed_reg(hwif, 0x0b) & 0x04)
		return ATA_CBL_PATA40;
	else
		return ATA_CBL_PATA80;
}
