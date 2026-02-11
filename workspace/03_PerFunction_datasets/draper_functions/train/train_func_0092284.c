read_memory(int space, Uint16 address)
{

	if (address<0x100) {
		return dsp_core->ramint[space][address] & BITMASK(24);
	}

	if (space==DSP_SPACE_P) {
		return read_memory_p(address);
	}


	if ((dsp_core->registers[DSP_REG_OMR] & (1<<DSP_OMR_DE)) &&
		(address<0x200)) {
		return dsp_core->rom[space][address] & BITMASK(24);
	}


	if (address >= 0xffc0) {
		Uint32 value;

		dsp_core->lockMutex(dsp_core);
		if ((space==DSP_SPACE_X) && (address==0xffc0+DSP_HOST_HRX)) {
			dsp_core_hostport_dspread(dsp_core);
		}
		value = dsp_core->periph[space][address-0xffc0] & BITMASK(24);
		dsp_core->unlockMutex(dsp_core);

		return value;
	}


	if (space == DSP_SPACE_X) {
		address += DSP_RAMSIZE>>1;
	}


	return dsp_core->ram[DSP_SPACE_P][address & (DSP_RAMSIZE-1)] & BITMASK(24);
}
