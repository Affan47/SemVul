l2cmd(u_char cmd)
{
	switch (cmd & ~0x10) {
	case 1:
		return "RR";
	case 5:
		return "RNR";
	case 9:
		return "REJ";
	case 0x6f:
		return "SABME";
	case 0x0f:
		return "DM";
	case 3:
		return "UI";
	case 0x43:
		return "DISC";
	case 0x63:
		return "UA";
	case 0x87:
		return "FRMR";
	case 0xaf:
		return "XID";
	default:
		if (!(cmd & 1))
			return "I";
		else
			return "invalid command";
	}
}
