__subn_set_opa_cc_table(struct opa_smp *smp, u32 am, u8 *data,
				   struct ib_device *ibdev, u8 port,
				   u32 *resp_len)
{
	struct ib_cc_table_attr *p = (struct ib_cc_table_attr *) data;
	struct hfi1_ibport *ibp = to_iport(ibdev, port);
	struct hfi1_pportdata *ppd = ppd_from_ibp(ibp);
	u32 start_block = OPA_AM_START_BLK(am);
	u32 n_blocks = OPA_AM_NBLK(am);
	struct ib_cc_table_entry_shadow *entries;
	int i, j;
	u32 sentry, eentry;
	u16 ccti_limit;
	struct cc_state *old_cc_state, *new_cc_state;


	if (n_blocks == 0 ||
	    start_block + n_blocks > ppd->cc_max_table_entries) {
		smp->status |= IB_SMP_INVALID_FIELD;
		return reply((struct ib_mad_hdr *)smp);
	}

	sentry = start_block * IB_CCT_ENTRIES;
	eentry = sentry + ((n_blocks - 1) * IB_CCT_ENTRIES) +
		 (be16_to_cpu(p->ccti_limit)) % IB_CCT_ENTRIES + 1;


	ccti_limit = be16_to_cpu(p->ccti_limit);
	if (ccti_limit + 1 > eentry) {
		smp->status |= IB_SMP_INVALID_FIELD;
		return reply((struct ib_mad_hdr *)smp);
	}

	new_cc_state = kzalloc(sizeof(*new_cc_state), GFP_KERNEL);
	if (new_cc_state == NULL)
		goto getit;

	spin_lock(&ppd->cc_state_lock);

	old_cc_state = get_cc_state(ppd);

	if (old_cc_state == NULL) {
		spin_unlock(&ppd->cc_state_lock);
		kfree(new_cc_state);
		return reply((struct ib_mad_hdr *)smp);
	}

	*new_cc_state = *old_cc_state;

	new_cc_state->cct.ccti_limit = ccti_limit;

	entries = ppd->ccti_entries;
	ppd->total_cct_entry = ccti_limit + 1;

	for (j = 0, i = sentry; i < eentry; j++, i++)
		entries[i].entry = be16_to_cpu(p->ccti_entries[j].entry);

	memcpy(new_cc_state->cct.entries, entries,
	       eentry * sizeof(struct ib_cc_table_entry));

	new_cc_state->cong_setting.port_control = IB_CC_CCS_PC_SL_BASED;
	new_cc_state->cong_setting.control_map = ppd->cc_sl_control_map;
	memcpy(new_cc_state->cong_setting.entries, ppd->congestion_entries,
	       OPA_MAX_SLS * sizeof(struct opa_congestion_setting_entry));

	rcu_assign_pointer(ppd->cc_state, new_cc_state);

	spin_unlock(&ppd->cc_state_lock);

	call_rcu(&old_cc_state->rcu, cc_state_reclaim);

getit:
	return __subn_get_opa_cc_table(smp, am, data, ibdev, port, resp_len);
}
