add_full_mgmt_pkey(struct hfi1_pportdata *ppd)
{
	struct hfi1_devdata *dd = ppd->dd;


	if (ppd->pkeys[2] != 0)
		dd_dev_err(dd, "%s pkey[2] already set to 0x%x, resetting it to 0x%x\n",
			   __func__, ppd->pkeys[2], FULL_MGMT_P_KEY);
	ppd->pkeys[2] = FULL_MGMT_P_KEY;
	(void)hfi1_set_ib_cfg(ppd, HFI1_IB_CFG_PKEYS, 0);
}
