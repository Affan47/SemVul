es5506_reg_read_test(struct ES5506Chip *chip, struct ES5506Voice *voice, offs_t offset)
{
	UINT32 result = 0;

	switch (offset)
	{
		case 0x68/8:
			if (chip->port_read)
				result = (*chip->port_read)();
			break;

		case 0x70/8:
			result = chip->irqv;
			break;

		case 0x78/8:
			result = chip->current_page;
			break;
	}
	return result;
}
