wlc_lcnphy_agc_temp_init(struct brcms_phy *pi)
{
	s16 temp;
	struct phytbl_info tab;
	u32 tableBuffer[2];
	struct brcms_phy_lcnphy *pi_lcn = pi->u.pi_lcnphy;

	temp = (s16) read_phy_reg(pi, 0x4df);
	pi_lcn->lcnphy_ofdmgainidxtableoffset = (temp & (0xff << 0)) >> 0;

	if (pi_lcn->lcnphy_ofdmgainidxtableoffset > 127)
		pi_lcn->lcnphy_ofdmgainidxtableoffset -= 256;

	pi_lcn->lcnphy_dsssgainidxtableoffset = (temp & (0xff << 8)) >> 8;

	if (pi_lcn->lcnphy_dsssgainidxtableoffset > 127)
		pi_lcn->lcnphy_dsssgainidxtableoffset -= 256;

	tab.tbl_ptr = tableBuffer;
	tab.tbl_len = 2;
	tab.tbl_id = 17;
	tab.tbl_offset = 59;
	tab.tbl_width = 32;
	wlc_lcnphy_read_table(pi, &tab);

	if (tableBuffer[0] > 63)
		tableBuffer[0] -= 128;
	pi_lcn->lcnphy_tr_R_gain_val = tableBuffer[0];

	if (tableBuffer[1] > 63)
		tableBuffer[1] -= 128;
	pi_lcn->lcnphy_tr_T_gain_val = tableBuffer[1];

	temp = (s16) (read_phy_reg(pi, 0x434) & (0xff << 0));
	if (temp > 127)
		temp -= 256;
	pi_lcn->lcnphy_input_pwr_offset_db = (s8) temp;

	pi_lcn->lcnphy_Med_Low_Gain_db =
		(read_phy_reg(pi, 0x424) & (0xff << 8)) >> 8;
	pi_lcn->lcnphy_Very_Low_Gain_db =
		(read_phy_reg(pi, 0x425) & (0xff << 0)) >> 0;

	tab.tbl_ptr = tableBuffer;
	tab.tbl_len = 2;
	tab.tbl_id = LCNPHY_TBL_ID_GAIN_IDX;
	tab.tbl_offset = 28;
	tab.tbl_width = 32;
	wlc_lcnphy_read_table(pi, &tab);

	pi_lcn->lcnphy_gain_idx_14_lowword = tableBuffer[0];
	pi_lcn->lcnphy_gain_idx_14_hiword = tableBuffer[1];

}
