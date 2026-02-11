mlx4_ib_process_mad(struct ib_device *ibdev, int mad_flags, u8 port_num,
			const struct ib_wc *in_wc, const struct ib_grh *in_grh,
			const struct ib_mad_hdr *in, size_t in_mad_size,
			struct ib_mad_hdr *out, size_t *out_mad_size,
			u16 *out_mad_pkey_index)
{
	struct mlx4_ib_dev *dev = to_mdev(ibdev);
	const struct ib_mad *in_mad = (const struct ib_mad *)in;
	struct ib_mad *out_mad = (struct ib_mad *)out;
	enum rdma_link_layer link = rdma_port_get_link_layer(ibdev, port_num);

	if (WARN_ON_ONCE(in_mad_size != sizeof(*in_mad) ||
			 *out_mad_size != sizeof(*out_mad)))
		return IB_MAD_RESULT_FAILURE;


	if (link == IB_LINK_LAYER_INFINIBAND) {
		if (mlx4_is_slave(dev->dev) &&
		    in_mad->mad_hdr.mgmt_class == IB_MGMT_CLASS_PERF_MGMT &&
		    in_mad->mad_hdr.attr_id == IB_PMA_PORT_COUNTERS)
			return iboe_process_mad(ibdev, mad_flags, port_num, in_wc,
						in_grh, in_mad, out_mad);

		return ib_process_mad(ibdev, mad_flags, port_num, in_wc,
				      in_grh, in_mad, out_mad);
	}

	if (link == IB_LINK_LAYER_ETHERNET)
		return iboe_process_mad(ibdev, mad_flags, port_num, in_wc,
					in_grh, in_mad, out_mad);

	return -EINVAL;
}
