bnx2x_exeq_get_mac(
	struct bnx2x_exe_queue_obj *o,
	struct bnx2x_exeq_elem *elem)
{
	struct bnx2x_exeq_elem *pos;
	struct bnx2x_mac_ramrod_data *data = &elem->cmd_data.vlan_mac.u.mac;


	list_for_each_entry(pos, &o->exe_queue, link)
		if (!memcmp(&pos->cmd_data.vlan_mac.u.mac, data,
			      sizeof(*data)) &&
		    (pos->cmd_data.vlan_mac.cmd == elem->cmd_data.vlan_mac.cmd))
			return pos;

	return NULL;
}
