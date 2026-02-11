PlotCmd_from_tmpfile(void)
{
	PlotCmd cmd;

	if (!silent_mode && !again)
		switch (vec_cntr_r++) {
		case 0:
			Eprintf("\nProcessing Cmd: ");
			break;
		case 1:
			Eprintf("1 ");
			break;
		case 2:
			Eprintf("2 ");
			break;
		case 5:
			Eprintf("5 ");
			break;
		case 10:
			Eprintf("10 ");
			break;
		case 20:
			Eprintf("20 ");
			break;
		case 50:
			Eprintf("50 ");
			break;
		case 100:
			Eprintf("100 ");
			break;
		case 200:
			Eprintf("200 ");
			break;
		case 500:
			Eprintf("500 ");
			break;
		case 1000:
			Eprintf("1k ");
			break;
		case 2000:
			Eprintf("2k ");
			break;
		case 5000:
			Eprintf("5k ");
			break;
		case 10000:
			Eprintf("10k ");
			break;
		case 20000:
			Eprintf("20k ");
			break;
		case 50000L:
			Eprintf("50k ");
			break;
		case 100000L:
			Eprintf("100k ");
			break;
		case 200000L:
			Eprintf("200k ");
			break;
		case 500000L:
			Eprintf("500k ");
			break;
		}

	switch (cmd = fgetc(td)) {
	case NOP:
	case MOVE_TO:
	case DRAW_TO:
	case PLOT_AT:
	case SET_PEN:
	case DEF_PW:
	case DEF_PC:
	case DEF_LA:
		return cmd;
	case (unsigned int) EOF:
	default:
		return CMD_EOF;
	}
}
