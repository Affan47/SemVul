es5506_reg_write_test(struct ES5506Chip *chip, struct ES5506Voice *voice, offs_t offset, UINT32 data)
{
	switch (offset)
	{
#ifdef LOG_COMMANDS
		case 0x00/8:
			if (LOG_COMMANDS && eslog)
				fprintf(eslog, "Channel 0 left test write %08x\n", data);
			break;
		case 0x08/8:
			if (LOG_COMMANDS && eslog)
				fprintf(eslog, "Channel 0 right test write %08x\n", data);
			break;
		case 0x10/8:
			if (LOG_COMMANDS && eslog)
				fprintf(eslog, "Channel 1 left test write %08x\n", data);
			break;

		case 0x18/8:
			if (LOG_COMMANDS && eslog)
				fprintf(eslog, "Channel 1 right test write %08x\n", data);
			break;

		case 0x20/8:
			if (LOG_COMMANDS && eslog)
				fprintf(eslog, "Channel 2 left test write %08x\n", data);
			break;

		case 0x28/8:
			if (LOG_COMMANDS && eslog)
				fprintf(eslog, "Channel 2 right test write %08x\n", data);
			break;

		case 0x30/8:
			if (LOG_COMMANDS && eslog)
				fprintf(eslog, "Channel 3 left test write %08x\n", data);
			break;

		case 0x38/8:
			if (LOG_COMMANDS && eslog)
				fprintf(eslog, "Channel 3 right test write %08x\n", data);
			break;

		case 0x40/8:
			if (LOG_COMMANDS && eslog)
				fprintf(eslog, "Channel 4 left test write %08x\n", data);
			break;

		case 0x48/8:
			if (LOG_COMMANDS && eslog)
				fprintf(eslog, "Channel 4 right test write %08x\n", data);
			break;

		case 0x50/8:
			if (LOG_COMMANDS && eslog)
				fprintf(eslog, "Channel 5 left test write %08x\n", data);
			break;

		case 0x58/8:
			if (LOG_COMMANDS && eslog)
				fprintf(eslog, "Channel 5 right test write %08x\n", data);
			break;

		case 0x60/8:
			if (LOG_COMMANDS && eslog)
				fprintf(eslog, "Test write EMPTY %08x\n", data);
			break;
#endif
		case 0x68/8:
		case 0x70/8:
			break;

		case 0x78/8:
			chip->current_page = data & 0x7f;
			break;
	}
}
