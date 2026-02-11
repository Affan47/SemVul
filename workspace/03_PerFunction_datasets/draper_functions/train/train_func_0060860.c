dev_rcv_packets(struct dev_info *hw_priv)
{
	int next;
	union desc_stat status;
	struct ksz_hw *hw = &hw_priv->hw;
	struct net_device *dev = hw->port_info[0].pdev;
	struct ksz_desc_info *info = &hw->rx_desc_info;
	int left = info->alloc;
	struct ksz_desc *desc;
	int received = 0;

	next = info->next;
	while (left--) {

		desc = &info->ring[next];
		status.data = le32_to_cpu(desc->phw->ctrl.data);
		if (status.rx.hw_owned)
			break;


		if (status.rx.last_desc && status.rx.first_desc) {
			if (rx_proc(dev, hw, desc, status))
				goto release_packet;
			received++;
		}

release_packet:
		release_desc(desc);
		next++;
		next &= info->mask;
	}
	info->next = next;

	return received;
}
