mlx4_slaves_closest_port(struct mlx4_dev *dev, int slave, int port)
{
	struct mlx4_active_ports actv_ports = mlx4_get_active_ports(dev, slave);
	int min_port = find_first_bit(actv_ports.ports, dev->caps.num_ports)
			+ 1;
	int max_port = min_port +
		bitmap_weight(actv_ports.ports, dev->caps.num_ports);

	if (port < min_port)
		port = min_port;
	else if (port >= max_port)
		port = max_port - 1;

	return port;
}
