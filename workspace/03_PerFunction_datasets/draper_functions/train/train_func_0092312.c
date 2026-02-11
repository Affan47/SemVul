write_memory_raw(int space, Uint16 address, Uint32 value)
{
	value &= BITMASK(24);


	if (address<0x100) {
		dsp_core->ramint[space][address] = value;
		return;
	}

	switch(space) {
		case DSP_SPACE_X:

			if ((dsp_core->registers[DSP_REG_OMR] & (1<<DSP_OMR_DE)) &&
				(address<0x200)) {

				return;
			}

			if (address >= 0xffc0) {
				dsp_core->lockMutex(dsp_core);
				switch(address-0xffc0) {
					case DSP_HOST_HTX:
						dsp_core->periph[DSP_SPACE_X][DSP_HOST_HTX] = value;

						dsp_core_hostport_dspwrite(dsp_core);
						break;
					case DSP_HOST_HCR:
						dsp_core->periph[DSP_SPACE_X][DSP_HOST_HCR] = value;

						dsp_core->hostport[CPU_HOST_ISR] &=
							BITMASK(8)-((1<<CPU_HOST_ISR_HF3)|(1<<CPU_HOST_ISR_HF2));
						dsp_core->hostport[CPU_HOST_ISR] |=
							dsp_core->periph[DSP_SPACE_X][DSP_HOST_HCR] & ((1<<CPU_HOST_ISR_HF3)|(1<<CPU_HOST_ISR_HF2));
						break;
					case DSP_HOST_HSR:

						break;
					default:
						dsp_core->periph[DSP_SPACE_X][address-0xffc0] = value;
						break;
				}
				dsp_core->unlockMutex(dsp_core);
				return;
			}

			address += DSP_RAMSIZE>>1;
			break;
		case DSP_SPACE_Y:

			if ((dsp_core->registers[DSP_REG_OMR] & (1<<DSP_OMR_DE)) &&
				(address<0x200)) {

				return;
			}

			if (address >= 0xffc0) {
				dsp_core->periph[DSP_SPACE_Y][address-0xffc0] = value;
				return;
			}
			break;
		case DSP_SPACE_P:

			if (address<0x200) {
				dsp_core->ramint[DSP_SPACE_P][address] = value;
				return;
			}
			break;
	}


	dsp_core->ram[DSP_SPACE_P][address & (DSP_RAMSIZE-1)] = value;
}
