sgh_l760_fixup(unsigned char prev, unsigned char curr)
{
	switch (curr) {
	case 0x98:
		switch (prev) {
		case 0xC4:
			return 0x99;
		default:
			return curr;
		}
	case 0xA3:
		switch (prev) {
		case 0xC4:
			return 0x98;
		case 0xC5:
			return 0x94;
		default:
			return curr;
		}
	case 0xA9:
		switch (prev) {
		case 0xC5:
			return 0x95;
		default:
			return curr;
		}
	default:
		return curr;
	}
}
