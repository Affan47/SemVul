dsp_jset(void)
{
	Uint32 memspace, addr, value, numreg, numbit;
	Uint32 newpc;

	memspace = (cur_inst>>6) & 1;
	value = (cur_inst>>8) & BITMASK(6);
	numbit = cur_inst & BITMASK(5);

	switch((cur_inst>>14) & BITMASK(2)) {
		case 0:


			addr = value;
			value = read_memory(memspace, addr);
			break;
		case 1:


			dsp_calc_ea(value, &addr);
			value = read_memory(memspace, addr);
			break;
		case 2:


			addr = 0xffc0 + value;
			value = read_memory(memspace, addr);
			break;
		case 3:

			numreg = value;
			if ((numreg==DSP_REG_A) || (numreg==DSP_REG_B)) {
				numreg = DSP_REG_A1+(numreg & 1);
			}
			value = dsp_core->registers[numreg];
			break;
	}

	++cur_inst_len;
	if (value & (1<<numbit)) {
		newpc = read_memory_p(dsp_core->pc+1);

		dsp_core->pc = newpc;
		cur_inst_len=0;
	}
}
