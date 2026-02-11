rtl88eu_dm_set_tx_ant_by_tx_info(struct odm_dm_struct *dm_odm,
				      u8 *desc, u8 mac_id)
{
	struct fast_ant_train *dm_fat_tbl = &dm_odm->DM_FatTable;

	if ((dm_odm->AntDivType == CG_TRX_HW_ANTDIV) ||
	    (dm_odm->AntDivType == CG_TRX_SMART_ANTDIV)) {
		SET_TX_DESC_ANTSEL_A_88E(desc, dm_fat_tbl->antsel_a[mac_id]);
		SET_TX_DESC_ANTSEL_B_88E(desc, dm_fat_tbl->antsel_b[mac_id]);
		SET_TX_DESC_ANTSEL_C_88E(desc, dm_fat_tbl->antsel_c[mac_id]);
	}
}
