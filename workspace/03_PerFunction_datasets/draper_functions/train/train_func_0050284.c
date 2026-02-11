hisi_nfc_read_byte(struct mtd_info *mtd)
{
	struct nand_chip *chip = mtd->priv;
	struct hinfc_host *host = chip->priv;

	if (host->command == NAND_CMD_STATUS)
		return *(uint8_t *)(host->mmio);

	host->offset++;

	if (host->command == NAND_CMD_READID)
		return *(uint8_t *)(host->mmio + host->offset - 1);

	return *(uint8_t *)(host->buffer + host->offset - 1);
}
