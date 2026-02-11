usnic_transport_unrsrv_port(enum usnic_transport_type type, u16 port_num)
{
	if (type == USNIC_TRANSPORT_ROCE_CUSTOM) {
		spin_lock(&roce_bitmap_lock);
		if (!port_num) {
			usnic_err("Unreserved unvalid port num 0 for %s\n",
					usnic_transport_to_str(type));
			goto out_roce_custom;
		}

		if (!test_bit(port_num, roce_bitmap)) {
			usnic_err("Unreserving invalid %hu for %s\n",
					port_num,
					usnic_transport_to_str(type));
			goto out_roce_custom;
		}
		bitmap_clear(roce_bitmap, port_num, 1);
		usnic_dbg("Freeing port %hu for %s\n", port_num,
				usnic_transport_to_str(type));
out_roce_custom:
		spin_unlock(&roce_bitmap_lock);
	} else {
		usnic_err("Freeing invalid port %hu for %d\n", port_num, type);
	}
}
