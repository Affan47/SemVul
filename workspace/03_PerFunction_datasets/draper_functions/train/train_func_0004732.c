dsp_tcc(void)
{
	Uint32 cc_code, regsrc1, regdest1, value;
	Uint32 regsrc2, regdest2;

	cc_code = (cur_inst>>12) & BITMASK(4);

	if (dsp_calc_cc(cc_code)) {
		regsrc1 = registers_tcc[(cur_inst>>3) & BITMASK(4)][0];
		regdest1 = registers_tcc[(cur_inst>>3) & BITMASK(4)][1];


		if ((regsrc1 == DSP_REG_A) || (regsrc1 == DSP_REG_B)) {
			tmp_parmove_src[0][0]=dsp_core->registers[DSP_REG_A2+(regsrc1 & 1)];
			tmp_parmove_src[0][1]=dsp_core->registers[DSP_REG_A1+(regsrc1 & 1)];
			tmp_parmove_src[0][2]=dsp_core->registers[DSP_REG_A0+(regsrc1 & 1)];
		} else {
			value = dsp_core->registers[regsrc1];
			tmp_parmove_src[0][0]=0;
			if (value & (1<<23)) {
				tmp_parmove_src[0][0]=0x0000ff;
			}
			tmp_parmove_src[0][1]=value;
			tmp_parmove_src[0][2]=0;
		}


		dsp_core->registers[DSP_REG_A2+(regdest1 & 1)]=tmp_parmove_src[0][0];
		dsp_core->registers[DSP_REG_A1+(regdest1 & 1)]=tmp_parmove_src[0][1];
		dsp_core->registers[DSP_REG_A0+(regdest1 & 1)]=tmp_parmove_src[0][2];


		if (cur_inst & (1<<16)) {
			regsrc2 = DSP_REG_R0+((cur_inst>>8) & BITMASK(3));
			regdest2 = DSP_REG_R0+(cur_inst & BITMASK(3));

			dsp_core->registers[regdest2] = dsp_core->registers[regsrc2];
		}
	}
}
