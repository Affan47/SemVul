ocrdma_parse_dcbxcfg_rsp(struct ocrdma_dev *dev, int ptype,
				    struct ocrdma_dcbx_cfg *dcbxcfg,
				    u8 *srvc_lvl)
{
	int status = -EINVAL, indx, slindx;
	int ventry_cnt;
	struct ocrdma_app_parameter *app_param;
	u8 valid, proto_sel;
	u8 app_prio, pfc_prio;
	u16 proto;

	if (!(dcbxcfg->tcv_aev_opv_st & OCRDMA_DCBX_STATE_MASK)) {
		pr_info("%s ocrdma%d DCBX is disabled\n",
			dev_name(&dev->nic_info.pdev->dev), dev->id);
		goto out;
	}

	if (!ocrdma_is_enabled_and_synced(dcbxcfg->pfc_state)) {
		pr_info("%s ocrdma%d priority flow control(%s) is %s%s\n",
			dev_name(&dev->nic_info.pdev->dev), dev->id,
			(ptype > 0 ? "operational" : "admin"),
			(dcbxcfg->pfc_state & OCRDMA_STATE_FLAG_ENABLED) ?
			"enabled" : "disabled",
			(dcbxcfg->pfc_state & OCRDMA_STATE_FLAG_SYNC) ?
			"" : ", not sync'ed");
		goto out;
	} else {
		pr_info("%s ocrdma%d priority flow control is enabled and sync'ed\n",
			dev_name(&dev->nic_info.pdev->dev), dev->id);
	}

	ventry_cnt = (dcbxcfg->tcv_aev_opv_st >>
				OCRDMA_DCBX_APP_ENTRY_SHIFT)
				& OCRDMA_DCBX_STATE_MASK;

	for (indx = 0; indx < ventry_cnt; indx++) {
		app_param = &dcbxcfg->app_param[indx];
		valid = (app_param->valid_proto_app >>
				OCRDMA_APP_PARAM_VALID_SHIFT)
				& OCRDMA_APP_PARAM_VALID_MASK;
		proto_sel = (app_param->valid_proto_app
				>>  OCRDMA_APP_PARAM_PROTO_SEL_SHIFT)
				& OCRDMA_APP_PARAM_PROTO_SEL_MASK;
		proto = app_param->valid_proto_app &
				OCRDMA_APP_PARAM_APP_PROTO_MASK;

		if (
			valid && proto == OCRDMA_APP_PROTO_ROCE &&
			proto_sel == OCRDMA_PROTO_SELECT_L2) {
			for (slindx = 0; slindx <
				OCRDMA_MAX_SERVICE_LEVEL_INDEX; slindx++) {
				app_prio = ocrdma_get_app_prio(
						(u8 *)app_param->app_prio,
						slindx);
				pfc_prio = ocrdma_get_pfc_prio(
						(u8 *)dcbxcfg->pfc_prio,
						slindx);

				if (app_prio && pfc_prio) {
					*srvc_lvl = slindx;
					status = 0;
					goto out;
				}
			}
			if (slindx == OCRDMA_MAX_SERVICE_LEVEL_INDEX) {
				pr_info("%s ocrdma%d application priority not set for 0x%x protocol\n",
					dev_name(&dev->nic_info.pdev->dev),
					dev->id, proto);
			}
		}
	}

out:
	return status;
}
