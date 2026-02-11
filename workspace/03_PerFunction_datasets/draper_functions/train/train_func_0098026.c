ncr_reset (void)
{
	board_mask = 131072 - 1;
	configured = 0;
	if (currprefs.cs_mbdmac == 2) {
		board_mask = 65535 - 1;
		configured = -1;
	}
}
