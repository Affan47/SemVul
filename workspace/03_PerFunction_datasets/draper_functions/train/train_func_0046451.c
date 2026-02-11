hisi_nfc_cmdfunc(struct mtd_info *mtd, unsigned command, int column,
		int page_addr)
{
	struct nand_chip *chip = mtd->priv;
	struct hinfc_host *host = chip->priv;
	int is_cache_invalid = 1;
	unsigned int flag = 0;

	host->command =  command;

	switch (command) {
	case NAND_CMD_READ0:
	case NAND_CMD_READOOB:
		if (command == NAND_CMD_READ0)
			host->offset = column;
		else
			host->offset = column + mtd->writesize;

		is_cache_invalid = 0;
		set_addr(mtd, column, page_addr);
		hisi_nfc_send_cmd_readstart(host);
		break;

	case NAND_CMD_SEQIN:
		host->offset = column;
		set_addr(mtd, column, page_addr);
		break;

	case NAND_CMD_ERASE1:
		set_addr(mtd, column, page_addr);
		break;

	case NAND_CMD_PAGEPROG:
		hisi_nfc_send_cmd_pageprog(host);
		break;

	case NAND_CMD_ERASE2:
		hisi_nfc_send_cmd_erase(host);
		break;

	case NAND_CMD_READID:
		host->offset = column;
		memset(host->mmio, 0, 0x10);
		hisi_nfc_send_cmd_readid(host);
		break;

	case NAND_CMD_STATUS:
		flag = hinfc_read(host, HINFC504_CON);
		if (chip->ecc.mode == NAND_ECC_HW)
			hinfc_write(host,
				    flag & ~(HINFC504_CON_ECCTYPE_MASK <<
				    HINFC504_CON_ECCTYPE_SHIFT), HINFC504_CON);

		host->offset = 0;
		memset(host->mmio, 0, 0x10);
		hisi_nfc_send_cmd_status(host);
		hinfc_write(host, flag, HINFC504_CON);
		break;

	case NAND_CMD_RESET:
		hisi_nfc_send_cmd_reset(host, host->chipselect);
		break;

	default:
		dev_err(host->dev, "Error: unsupported cmd(cmd=%x, col=%x, page=%x)\n",
			command, column, page_addr);
	}

	if (is_cache_invalid) {
		host->cache_addr_value[0] = ~0;
		host->cache_addr_value[1] = ~0;
	}
}
