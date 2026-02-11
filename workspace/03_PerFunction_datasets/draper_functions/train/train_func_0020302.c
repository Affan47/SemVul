bnx2x_set_one_vlan_e2(struct bnx2x *bp,
				  struct bnx2x_vlan_mac_obj *o,
				  struct bnx2x_exeq_elem *elem, int rule_idx,
				  int cam_offset)
{
	struct bnx2x_raw_obj *raw = &o->raw;
	struct eth_classify_rules_ramrod_data *data =
		(struct eth_classify_rules_ramrod_data *)(raw->rdata);
	int rule_cnt = rule_idx + 1;
	union eth_classify_rule_cmd *rule_entry = &data->rules[rule_idx];
	enum bnx2x_vlan_mac_cmd cmd = elem->cmd_data.vlan_mac.cmd;
	bool add = (cmd == BNX2X_VLAN_MAC_ADD) ? true : false;
	u16 vlan = elem->cmd_data.vlan_mac.u.vlan.vlan;


	if (rule_idx == 0)
		memset(data, 0, sizeof(*data));


	bnx2x_vlan_mac_set_cmd_hdr_e2(bp, o, add, CLASSIFY_RULE_OPCODE_VLAN,
				      &rule_entry->vlan.header);

	DP(BNX2X_MSG_SP, "About to %s VLAN %d\n", (add ? "add" : "delete"),
			 vlan);


	rule_entry->vlan.vlan = cpu_to_le16(vlan);


	if (cmd == BNX2X_VLAN_MAC_MOVE) {
		rule_entry++;
		rule_cnt++;


		bnx2x_vlan_mac_set_cmd_hdr_e2(bp,
					elem->cmd_data.vlan_mac.target_obj,
					      true, CLASSIFY_RULE_OPCODE_VLAN,
					      &rule_entry->vlan.header);


		rule_entry->vlan.vlan = cpu_to_le16(vlan);
	}


	bnx2x_vlan_mac_set_rdata_hdr_e2(raw->cid, raw->state, &data->header,
					rule_cnt);
}
