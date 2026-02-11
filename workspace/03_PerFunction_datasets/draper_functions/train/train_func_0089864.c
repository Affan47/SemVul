rtl8188e_set_FwMediaStatus_cmd(struct adapter *adapt, __le16 mstatus_rpt)
{
	u8 opmode, macid;
	u16 mst_rpt = le16_to_cpu(mstatus_rpt);
	opmode = (u8)mst_rpt;
	macid = (u8)(mst_rpt >> 8);

	DBG_88E("### %s: MStatus=%x MACID=%d\n", __func__, opmode, macid);
	FillH2CCmd_88E(adapt, H2C_COM_MEDIA_STATUS_RPT, sizeof(mst_rpt), (u8 *)&mst_rpt);
}
