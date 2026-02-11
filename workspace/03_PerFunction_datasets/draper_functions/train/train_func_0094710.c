AF80_D6GetByte(UWORD addr, int no_side_effects)
{
	int result = 0xff;
	if (!not_enable_2k_character_ram) {
		result = MEMORY_dGetByte(addr);
	}
	else if (!not_enable_2k_attribute_ram) {
		result = MEMORY_dGetByte(addr);
	}
	else if (!not_enable_crtc_registers) {
		if (video_bank_select == 0 ) {
			if ((addr&0xff)<0x40) {
				result = crtreg[addr&0xff];
				if ((addr&0xff) == 0x3a) {
					result = 0x01;
				}
			}
			D(printf("AF80 Read addr:%4x cpu:%4x\n", addr, CPU_remember_PC[(CPU_remember_PC_curpos-1)%CPU_REMEMBER_PC_STEPS]));
		}
	}
	return result;
}
