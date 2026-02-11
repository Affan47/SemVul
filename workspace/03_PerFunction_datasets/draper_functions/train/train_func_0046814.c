dsp_mpyr(void)
{
	Uint32 srcreg1, srcreg2, destreg, value, dest[3], source[3];

	value = (cur_inst>>4) & BITMASK(3);
	srcreg1 = registers_mpy[value][0];
	srcreg2 = registers_mpy[value][1];

	dsp_mul56(dsp_core->registers[srcreg1], dsp_core->registers[srcreg2], source);

	destreg = (cur_inst>>3) & 1;
	if (cur_inst & (1<<2)) {
		dest[0] = dest[1] = dest[2] = 0;

		dsp_sub56(source, dest);
	} else {
		dest[0] = source[0];
		dest[1] = source[1];
		dest[2] = source[2];
	}

	dsp_rnd56(dest);

	dsp_core->registers[DSP_REG_A2+destreg] = dest[0];
	dsp_core->registers[DSP_REG_A1+destreg] = dest[1];
	dsp_core->registers[DSP_REG_A0+destreg] = dest[2];

	dsp_ccr_extension(&dest[0], &dest[1]);
	dsp_ccr_unnormalized(&dest[0], &dest[1]);
	dsp_ccr_negative(&dest[0]);
	dsp_ccr_zero(&dest[0], &dest[1], &dest[2]);

	dsp_core->registers[DSP_REG_SR] &= BITMASK(16)-(1<<DSP_SR_V);
}
