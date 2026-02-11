Devices_H_BinLoaderCont(void)
{
	if (binf == NULL)
		return;
	if (BINLOAD_start_binloading) {
		MEMORY_dPutByte(0x244, 0);
		MEMORY_dPutByte(0x09, 1);
	}
	else
		CPU_regS += 2;

	MEMORY_dPutByte(0x2e3, 0xd7);
	do {
		int temp;
		UWORD from;
		UWORD to;
		do
			temp = Devices_H_BinReadWord();
		while (temp == 0xffff);
		if (temp < 0)
			return;
		from = (UWORD) temp;

		temp = Devices_H_BinReadWord();
		if (temp < 0)
			return;
		to = (UWORD) temp;

		if (devbug)
			Log_print("H: Load: From %04X to %04X", from, to);

		if (BINLOAD_start_binloading) {
			if (runBinFile)
				MEMORY_dPutWordAligned(0x2e0, from);
			BINLOAD_start_binloading = FALSE;
		}

		to++;
		do {
			int byte = fgetc(binf);
			if (byte == EOF) {
				fclose(binf);
				binf = NULL;
				if (runBinFile)
					CPU_regPC = MEMORY_dGetWordAligned(0x2e0);
				if (initBinFile && (MEMORY_dGetByte(0x2e3) != 0xd7)) {

					CPU_regPC--;
					MEMORY_dPutByte(0x0100 + CPU_regS--, CPU_regPC >> 8);
					MEMORY_dPutByte(0x0100 + CPU_regS--, CPU_regPC & 0xff);
					CPU_regPC = MEMORY_dGetWordAligned(0x2e2);
				}
				return;
			}
			MEMORY_PutByte(from, (UBYTE) byte);
			from++;
		} while (from != to);
	} while (!initBinFile || MEMORY_dGetByte(0x2e3) == 0xd7);

	CPU_regS--;
	ESC_Add((UWORD) (0x100 + CPU_regS), ESC_BINLOADER_CONT, Devices_H_BinLoaderCont);
	CPU_regS--;
	MEMORY_dPutByte(0x0100 + CPU_regS--, 0x01);
	MEMORY_dPutByte(0x0100 + CPU_regS, CPU_regS + 1);
	CPU_regS--;
	CPU_regPC = MEMORY_dGetWordAligned(0x2e2);
	CPU_SetC;

	MEMORY_dPutByte(0x0300, 0x31);
}
