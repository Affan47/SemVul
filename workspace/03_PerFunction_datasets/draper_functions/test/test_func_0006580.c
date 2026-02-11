hscx_init(struct hscx_hw *hx)
{
	u8 val;

	WriteHSCX(hx, IPAC_RAH2, 0xFF);
	WriteHSCX(hx, IPAC_XBCH, 0x00);
	WriteHSCX(hx, IPAC_RLCR, 0x00);

	if (hx->ip->type & IPAC_TYPE_HSCX) {
		WriteHSCX(hx, IPAC_CCR1, 0x85);
		val = ReadHSCX(hx, HSCX_VSTR);
		pr_debug("%s: HSCX VSTR %02x\n", hx->ip->name, val);
		if (hx->bch.debug & DEBUG_HW)
			pr_notice("%s: HSCX version %s\n", hx->ip->name,
				  HSCXVer[val & 0x0f]);
	} else
		WriteHSCX(hx, IPAC_CCR1, 0x82);
	WriteHSCX(hx, IPAC_CCR2, 0x30);
	WriteHSCX(hx, IPAC_XCCR, 0x07);
	WriteHSCX(hx, IPAC_RCCR, 0x07);
}
