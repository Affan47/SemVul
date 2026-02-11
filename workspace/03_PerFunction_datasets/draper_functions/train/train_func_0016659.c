es5506_reg_read_high(struct ES5506Chip *chip, struct ES5506Voice *voice, offs_t offset)
{
	UINT32 result = 0;

	switch (offset)
	{
		case 0x00/8:
			result = voice->control;
			break;

		case 0x08/8:
			result = voice->start;
			break;

		case 0x10/8:
			result = voice->end;
			break;

		case 0x18/8:
			result = voice->accum;
			break;

		case 0x20/8:
			result = voice->o4n1 & 0x3ffff;
			break;

		case 0x28/8:
			result = voice->o3n1 & 0x3ffff;
			break;

		case 0x30/8:
			result = voice->o3n2 & 0x3ffff;
			break;

		case 0x38/8:
			result = voice->o2n1 & 0x3ffff;
			break;

		case 0x40/8:
			result = voice->o2n2 & 0x3ffff;
			break;

		case 0x48/8:
			result = voice->o1n1 & 0x3ffff;
			break;

		case 0x50/8:
			result = chip->wst;
			break;

		case 0x58/8:
			result = chip->wend;
			break;

		case 0x60/8:
			result = chip->lrend;
			break;

		case 0x68/8:
			if (chip->port_read)
				result = (*chip->port_read)();
			break;

		case 0x70/8:
			result = chip->irqv;
			update_internal_irq_state(chip);
			break;

		case 0x78/8:
			result = chip->current_page;
			break;
	}
	return result;
}
