bnx2x_check_vlan_add(struct bnx2x *bp,
				struct bnx2x_vlan_mac_obj *o,
				union bnx2x_classification_ramrod_data *data)
{
	struct bnx2x_vlan_mac_registry_elem *pos;

	DP(BNX2X_MSG_SP, "Checking VLAN %d for ADD command\n", data->vlan.vlan);

	list_for_each_entry(pos, &o->head, link)
		if (data->vlan.vlan == pos->u.vlan.vlan)
			return -EEXIST;

	return 0;
}
