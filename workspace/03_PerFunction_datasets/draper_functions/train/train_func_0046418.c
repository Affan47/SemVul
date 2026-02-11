onenand_sync_read_bufferram(struct mtd_info *mtd, int area,
		unsigned char *buffer, int offset, size_t count)
{
	struct onenand_chip *this = mtd->priv;
	void __iomem *bufferram;

	bufferram = this->base + area;

	bufferram += onenand_bufferram_offset(mtd, area);

	this->mmcontrol(mtd, ONENAND_SYS_CFG1_SYNC_READ);

	if (ONENAND_CHECK_BYTE_ACCESS(count)) {
		unsigned short word;


		count--;


		word = this->read_word(bufferram + offset + count);
		buffer[count] = (word & 0xff);
	}

	memcpy(buffer, bufferram + offset, count);

	this->mmcontrol(mtd, 0);

	return 0;
}
