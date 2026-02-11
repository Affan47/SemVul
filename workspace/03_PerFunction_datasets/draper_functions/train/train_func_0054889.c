usnic_vnic_check_room(struct usnic_vnic *vnic,
				struct usnic_vnic_res_spec *res_spec)
{
	int i;
	enum usnic_vnic_res_type res_type;
	int res_cnt;

	for (i = 0; i < USNIC_VNIC_RES_TYPE_MAX; i++) {
		res_type = res_spec->resources[i].type;
		res_cnt = res_spec->resources[i].cnt;

		if (res_type == USNIC_VNIC_RES_TYPE_EOL)
			break;

		if (res_cnt > usnic_vnic_res_free_cnt(vnic, res_type))
			return -EBUSY;
	}

	return 0;
}
