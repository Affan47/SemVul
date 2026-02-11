bringup_serdes(struct hfi1_pportdata *ppd)
{
	struct hfi1_devdata *dd = ppd->dd;
	u64 guid;
	int ret;

	if (HFI1_CAP_IS_KSET(EXTENDED_PSN))
		add_rcvctrl(dd, RCV_CTRL_RCV_EXTENDED_PSN_ENABLE_SMASK);

	guid = ppd->guid;
	if (!guid) {
		if (dd->base_guid)
			guid = dd->base_guid + ppd->port - 1;
		ppd->guid = guid;
	}


	ppd->link_enabled = 1;

	ppd->linkinit_reason = OPA_LINKINIT_REASON_LINKUP;

	if (loopback) {
		ret = init_loopback(dd);
		if (ret < 0)
			return ret;
	}

	return start_link(ppd);
}
