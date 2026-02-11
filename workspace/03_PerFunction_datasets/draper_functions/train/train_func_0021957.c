fjes_hw_check_vlan_id(struct epbuf_handler *epbh, u16 vlan_id)
{
	union ep_buffer_info *info = epbh->info;
	bool ret = false;
	int i;

	if (vlan_id == 0) {
		ret = true;
	} else {
		for (i = 0; i < EP_BUFFER_SUPPORT_VLAN_MAX; i++) {
			if (vlan_id == info->v1i.vlan_id[i]) {
				ret = true;
				break;
			}
		}
	}
	return ret;
}
