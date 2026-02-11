create_ib_ah(struct ib_ah_attr *ah_attr,
			   struct mlx5_ib_ah *ah)
{
	if (ah_attr->ah_flags & IB_AH_GRH) {
		memcpy(ah->av.rgid, &ah_attr->grh.dgid, 16);
		ah->av.grh_gid_fl = cpu_to_be32(ah_attr->grh.flow_label |
						(1 << 30) |
						ah_attr->grh.sgid_index << 20);
		ah->av.hop_limit = ah_attr->grh.hop_limit;
		ah->av.tclass = ah_attr->grh.traffic_class;
	}

	ah->av.rlid = cpu_to_be16(ah_attr->dlid);
	ah->av.fl_mlid = ah_attr->src_path_bits & 0x7f;
	ah->av.stat_rate_sl = (ah_attr->static_rate << 4) | (ah_attr->sl & 0xf);

	return &ah->ibah;
}
