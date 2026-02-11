dsp_movec_reg(void)
{
	Uint32 numreg1, numreg2, value;


	numreg2 = (cur_inst>>8) & BITMASK(6);
	numreg1 = cur_inst & BITMASK(6);

	if (cur_inst & (1<<15)) {


		if ((numreg2 == DSP_REG_A) || (numreg2 == DSP_REG_B)) {
			dsp_pm_read_accu24(numreg2, &dsp_core->registers[numreg1]);
		} else {
			dsp_core->registers[numreg1] = dsp_core->registers[numreg2];
		}
		dsp_core->registers[numreg1] &= BITMASK(registers_mask[numreg1]);
	} else {


		if ((numreg2 == DSP_REG_A) || (numreg2 == DSP_REG_B)) {
			value = dsp_core->registers[numreg1];
			dsp_core->registers[DSP_REG_A2+(numreg2 & 1)] = 0;
			if (value & (1<<23)) {
				dsp_core->registers[DSP_REG_A2+(numreg2 & 1)] = 0xff;
			}
			dsp_core->registers[DSP_REG_A1+(numreg2 & 1)] = value & BITMASK(24);
			dsp_core->registers[DSP_REG_A0+(numreg2 & 1)] = 0;
		} else {
			dsp_core->registers[numreg2] = dsp_core->registers[numreg1];
			dsp_core->registers[numreg2] &= BITMASK(registers_mask[numreg2]);
		}
	}
}
