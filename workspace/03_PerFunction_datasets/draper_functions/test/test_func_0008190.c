_rtl8723be_get_rate_section_index(u32 regaddr)
{
	u8 index = 0;

	switch (regaddr) {
	case RTXAGC_A_RATE18_06:
		index = 0;
	break;
	case RTXAGC_A_RATE54_24:
		index = 1;
	break;
	case RTXAGC_A_CCK1_MCS32:
		index = 2;
	break;
	case RTXAGC_B_CCK11_A_CCK2_11:
		index = 3;
	break;
	case RTXAGC_A_MCS03_MCS00:
		index = 4;
	break;
	case RTXAGC_A_MCS07_MCS04:
		index = 5;
	break;
	case RTXAGC_A_MCS11_MCS08:
		index = 6;
	break;
	case RTXAGC_A_MCS15_MCS12:
		index = 7;
	break;
	case RTXAGC_B_RATE18_06:
		index = 0;
	break;
	case RTXAGC_B_RATE54_24:
		index = 1;
	break;
	case RTXAGC_B_CCK1_55_MCS32:
		index = 2;
	break;
	case RTXAGC_B_MCS03_MCS00:
		index = 4;
	break;
	case RTXAGC_B_MCS07_MCS04:
		index = 5;
	break;
	case RTXAGC_B_MCS11_MCS08:
		index = 6;
	break;
	case RTXAGC_B_MCS15_MCS12:
		index = 7;
	break;
	default:
		regaddr &= 0xFFF;
		if (regaddr >= 0xC20 && regaddr <= 0xC4C)
			index = (u8)((regaddr - 0xC20) / 4);
		else if (regaddr >= 0xE20 && regaddr <= 0xE4C)
			index = (u8)((regaddr - 0xE20) / 4);
		break;
	};
	return index;
}
