part_erase(struct mtd_info *mtd, struct erase_info *instr)
{
	struct mtd_part *part = PART(mtd);
	int ret;

	instr->addr += part->offset;
	ret = part->master->_erase(part->master, instr);
	if (ret) {
		if (instr->fail_addr != MTD_FAIL_ADDR_UNKNOWN)
			instr->fail_addr -= part->offset;
		instr->addr -= part->offset;
	}
	return ret;
}
