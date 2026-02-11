dsp_pm_writereg(int numreg, int position)
{
	if ((numreg == DSP_REG_A) || (numreg == DSP_REG_B)) {
		tmp_parmove_dest[position][0].host_pointer=&dsp_core->registers[DSP_REG_A2+(numreg & 1)];
		tmp_parmove_dest[position][1].host_pointer=&dsp_core->registers[DSP_REG_A1+(numreg & 1)];
		tmp_parmove_dest[position][2].host_pointer=&dsp_core->registers[DSP_REG_A0+(numreg & 1)];

		tmp_parmove_start[position]=0;
		tmp_parmove_len[position]=3;
	} else {
		tmp_parmove_dest[position][1].host_pointer=&dsp_core->registers[numreg];

		tmp_parmove_start[position]=1;
		tmp_parmove_len[position]=1;
	}
}
