setFromDCS(FaxParams& dcs_caps)
{
    assign(dcs_caps);
    u_int dcs = 0;
    u_int xinfo = 0;

    dcs |= getByte(0) << 16;
    dcs |= getByte(1) << 8;
    dcs |= getByte(2) << 0;

    xinfo |= getByte(3) << 24;
    xinfo |= getByte(4) << 16;
    xinfo |= getByte(5) << 8;
    xinfo |= getByte(6) << 0;

    setFromDCS(dcs, xinfo);

    if (dcs_caps.isBitEnabled(FaxParams::BITNUM_LETTER_SIZE) ||
	dcs_caps.isBitEnabled(FaxParams::BITNUM_LEGAL_SIZE)) {

	wd = WD_A4;
	ln = LN_INF;
    }

    if (dcs_caps.isBitEnabled(FaxParams::BITNUM_JBIG_BASIC)) df = DF_JBIG;
    if (dcs_caps.isBitEnabled(FaxParams::BITNUM_JBIG_L0)) df = DF_JBIG;
    if (dcs_caps.isBitEnabled(FaxParams::BITNUM_JPEG)) jp = JP_GREY;
    if (dcs_caps.isBitEnabled(FaxParams::BITNUM_FULLCOLOR)) {
	if (jp == JP_GREY) jp = JP_COLOR;
    }
    if (ec == EC_DISABLE &&
	(df == DF_2DMMR || df == DF_JBIG || jp == JP_GREY || jp == JP_COLOR)) {


	ec = EC_ENABLE256;
    }
}
