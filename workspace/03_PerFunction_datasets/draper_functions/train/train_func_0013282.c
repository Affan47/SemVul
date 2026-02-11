flexonenand_block(struct onenand_chip *this, loff_t addr)
{
	unsigned boundary, blk, die = 0;

	if (ONENAND_IS_DDP(this) && addr >= this->diesize[0]) {
		die = 1;
		addr -= this->diesize[0];
	}

	boundary = this->boundary[die];

	blk = addr >> (this->erase_shift - 1);
	if (blk > boundary)
		blk = (blk + boundary + 1) >> 1;

	blk += die ? this->density_mask : 0;
	return blk;
}
