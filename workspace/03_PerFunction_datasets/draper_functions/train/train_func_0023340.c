ssb_chipco_get_clockcontrol(struct ssb_chipcommon *cc,
				 u32 *plltype, u32 *n, u32 *m)
{
	*n = chipco_read32(cc, SSB_CHIPCO_CLOCK_N);
	*plltype = (cc->capabilities & SSB_CHIPCO_CAP_PLLT);
	switch (*plltype) {
	case SSB_PLLTYPE_6:
		*m = chipco_read32(cc, SSB_CHIPCO_CLOCK_MIPS);
		break;
	case SSB_PLLTYPE_3:
		if (cc->dev->bus->chip_id != 0x5365) {
			*m = chipco_read32(cc, SSB_CHIPCO_CLOCK_M2);
			break;
		}

	default:
		*m = chipco_read32(cc, SSB_CHIPCO_CLOCK_SB);
	}
}
