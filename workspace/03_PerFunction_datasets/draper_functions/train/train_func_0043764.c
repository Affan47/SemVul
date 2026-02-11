r852_wait(struct mtd_info *mtd, struct nand_chip *chip)
{
	struct r852_device *dev = chip->priv;

	unsigned long timeout;
	int status;

	timeout = jiffies + (chip->state == FL_ERASING ?
		msecs_to_jiffies(400) : msecs_to_jiffies(20));

	while (time_before(jiffies, timeout))
		if (chip->dev_ready(mtd))
			break;

	chip->cmdfunc(mtd, NAND_CMD_STATUS, -1, -1);
	status = (int)chip->read_byte(mtd);


	if (dev->dma_error) {
		status |= NAND_STATUS_FAIL;
		dev->dma_error = 0;
	}
	return status;
}
