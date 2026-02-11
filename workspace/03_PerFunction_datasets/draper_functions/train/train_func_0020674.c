mlx4_check_port_params(struct mlx4_dev *dev,
			   enum mlx4_port_type *port_type)
{
	int i;

	if (!(dev->caps.flags & MLX4_DEV_CAP_FLAG_DPDP)) {
		for (i = 0; i < dev->caps.num_ports - 1; i++) {
			if (port_type[i] != port_type[i + 1]) {
				mlx4_err(dev, "Only same port types supported on this HCA, aborting\n");
				return -EINVAL;
			}
		}
	}

	for (i = 0; i < dev->caps.num_ports; i++) {
		if (!(port_type[i] & dev->caps.supported_type[i+1])) {
			mlx4_err(dev, "Requested port type for port %d is not supported on this HCA\n",
				 i + 1);
			return -EINVAL;
		}
	}
	return 0;
}
