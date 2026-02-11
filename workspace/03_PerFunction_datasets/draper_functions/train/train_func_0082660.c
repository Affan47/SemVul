bios_10_12xx(struct regs *regs)
{
#ifdef DEBUG_INT10
        dprintf("VGA Function 12: different sub-functions: BL=0x%02x\n", BL);
#endif
	if (BL == 0x10) {


		CH = 0x00;


		CL = var_get(switches) & 0x0f;


		if (var_get(vid_io) == 0x03d4) {
			BH = 0x00;
		} else {
			BH = 0x01;
		}


		BL = 0x03;

	} else if (BL == 0x20) {


	} else if (BL == 0x30) {
		AX = 0x1212;


	} else if (BL == 0x31) {
		AH = 0x31;
		for (;;);
		AL = 0x12;

	} else if (BL == 0x32) {
		AH = 0x32;
		for (;;);
		AL = 0x12;

	} else if (BL == 0x33) {
		AH = 0x33;
		for (;;);
		AL = 0x12;

	} else if (BL == 0x34) {


		AL = 0x12;

	} else if (BL == 0x35) {
		AH = 0x35;
		for (;;);
		AL = 0x12;

	} else if (BL == 0x36) {

		if (AL == 0) {

		} else {


		}
		AL = 0x12;

	} else {
#if 0
		for (;;);
#endif
	}
}
