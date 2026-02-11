read_word(void)
{
	UBYTE buf[2];
	if (fread(buf, 1, 2, BINLOAD_bin_file) != 2) {
		fclose(BINLOAD_bin_file);
		BINLOAD_bin_file = NULL;
		if (BINLOAD_start_binloading) {
			BINLOAD_start_binloading = FALSE;
			Log_print("binload: not valid BIN file");
			return -1;
		}
		CPU_regPC = MEMORY_dGetWordAligned(0x2e0);
		return -1;
	}
	return buf[0] + (buf[1] << 8);
}
