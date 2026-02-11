stv0900_set_symbol_rate(struct stv0900_internal *intp,
					u32 mclk, u32 srate,
					enum fe_stv0900_demod_num demod)
{
	u32 symb;

	dprintk("%s: Mclk %d, SR %d, Dmd %d\n", __func__, mclk,
							srate, demod);

	if (srate > 60000000) {
		symb = srate << 4;
		symb /= (mclk >> 12);
	} else if (srate > 6000000) {
		symb = srate << 6;
		symb /= (mclk >> 10);
	} else {
		symb = srate << 9;
		symb /= (mclk >> 7);
	}

	stv0900_write_reg(intp, SFRINIT1, (symb >> 8) & 0x7f);
	stv0900_write_reg(intp, SFRINIT1 + 1, (symb & 0xff));
}
