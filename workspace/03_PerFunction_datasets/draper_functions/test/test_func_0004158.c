vxge_restore_vpath_mac_addr(struct vxge_vpath *vpath)
{
	enum vxge_hw_status status = VXGE_HW_OK;
	struct macInfo mac_info;
	u8 *mac_address = NULL;
	struct list_head *entry, *next;

	memset(&mac_info, 0, sizeof(struct macInfo));

	if (vpath->is_open) {
		list_for_each_safe(entry, next, &vpath->mac_addr_list) {
			mac_address =
				(u8 *)&
				((struct vxge_mac_addrs *)entry)->macaddr;
			memcpy(mac_info.macaddr, mac_address, ETH_ALEN);
			((struct vxge_mac_addrs *)entry)->state =
				VXGE_LL_MAC_ADDR_IN_DA_TABLE;

			status = vxge_search_mac_addr_in_da_table(vpath,
				&mac_info);
			if (status != VXGE_HW_OK) {

				status = vxge_hw_vpath_mac_addr_add(
					vpath->handle, mac_info.macaddr,
					mac_info.macmask,
				    VXGE_HW_VPATH_MAC_ADDR_ADD_DUPLICATE);
				if (status != VXGE_HW_OK) {
					vxge_debug_init(VXGE_ERR,
					    "DA add entry failed for vpath:%d",
					    vpath->device_id);
					((struct vxge_mac_addrs *)entry)->state
						= VXGE_LL_MAC_ADDR_IN_LIST;
				}
			}
		}
	}

	return status;
}
