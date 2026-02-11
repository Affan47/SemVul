ib_init_ah_from_path(struct ib_device *device, u8 port_num,
			 struct ib_sa_path_rec *rec, struct ib_ah_attr *ah_attr)
{
	int ret;
	u16 gid_index;
	int force_grh;

	memset(ah_attr, 0, sizeof *ah_attr);
	ah_attr->dlid = be16_to_cpu(rec->dlid);
	ah_attr->sl = rec->sl;
	ah_attr->src_path_bits = be16_to_cpu(rec->slid) &
				 get_src_path_mask(device, port_num);
	ah_attr->port_num = port_num;
	ah_attr->static_rate = rec->rate;

	force_grh = rdma_cap_eth_ah(device, port_num);

	if (rec->hop_limit > 1 || force_grh) {
		struct net_device *ndev = ib_get_ndev_from_path(rec);

		ah_attr->ah_flags = IB_AH_GRH;
		ah_attr->grh.dgid = rec->dgid;

		ret = ib_find_cached_gid(device, &rec->sgid, ndev, &port_num,
					 &gid_index);
		if (ret) {
			if (ndev)
				dev_put(ndev);
			return ret;
		}

		ah_attr->grh.sgid_index    = gid_index;
		ah_attr->grh.flow_label    = be32_to_cpu(rec->flow_label);
		ah_attr->grh.hop_limit     = rec->hop_limit;
		ah_attr->grh.traffic_class = rec->traffic_class;
		if (ndev)
			dev_put(ndev);
	}
	if (force_grh) {
		memcpy(ah_attr->dmac, rec->dmac, ETH_ALEN);
	}
	return 0;
}
