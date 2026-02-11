MEMORY_HwGetByte(UWORD addr, int no_side_effects)
{
	UBYTE byte = 0xff;
	switch (addr & 0xff00) {
	case 0x4f00:
	case 0x8f00:
		if (!no_side_effects)
			CARTRIDGE_BountyBob1(addr);
		byte = 0;
		break;
	case 0x5f00:
	case 0x9f00:
		if (!no_side_effects)
			CARTRIDGE_BountyBob2(addr);
		byte = 0;
		break;
	case 0xd000:
	case 0xc000:
	case 0xc100:
	case 0xc200:
	case 0xc300:
	case 0xc400:
	case 0xc500:
	case 0xc600:
	case 0xc700:
	case 0xc800:
	case 0xc900:
	case 0xca00:
	case 0xcb00:
	case 0xcc00:
	case 0xcd00:
	case 0xce00:
		byte = GTIA_GetByte(addr, no_side_effects);
		break;
	case 0xd200:
	case 0xe800:
	case 0xe900:
	case 0xea00:
	case 0xeb00:
	case 0xec00:
	case 0xed00:
	case 0xee00:
	case 0xef00:
		byte = POKEY_GetByte(addr, no_side_effects);
		break;
	case 0xd300:
		byte = PIA_GetByte(addr, no_side_effects);
		break;
	case 0xd400:
		byte = ANTIC_GetByte(addr, no_side_effects);
		break;
	case 0xd500:
		byte = CARTRIDGE_GetByte(addr, no_side_effects);
		break;
	case 0xff00:
		byte = MosaicGetByte(addr, no_side_effects);
		break;
	case 0xcf00:
	case 0x0f00:
		if (Atari800_machine_type == Atari800_MACHINE_5200) {
			byte = GTIA_GetByte(addr, no_side_effects);
		}
		else {
			byte = AxlonGetByte(addr, no_side_effects);
		}
		break;
	case 0xd100:
		byte = PBI_D1GetByte(addr, no_side_effects);
		break;
	case 0xd600:
		byte = PBI_D6GetByte(addr, no_side_effects);
		break;
	case 0xd700:
		byte = PBI_D7GetByte(addr, no_side_effects);
		break;
	default:
		break;
	}

	return byte;
}
