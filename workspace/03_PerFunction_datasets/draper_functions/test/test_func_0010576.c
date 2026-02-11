ar5008_write_bank6(struct ath_hw *ah, unsigned int *writecnt)
{
	struct ar5416IniArray *array = &ah->iniBank6;
	u32 *data = ah->analogBank6Data;
	int r;

	ENABLE_REGWRITE_BUFFER(ah);

	for (r = 0; r < array->ia_rows; r++) {
		REG_WRITE(ah, INI_RA(array, r, 0), data[r]);
		DO_DELAY(*writecnt);
	}

	REGWRITE_BUFFER_FLUSH(ah);
}
