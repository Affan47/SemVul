mlx4_gen_guid_change_eqe(struct mlx4_dev *dev, int slave, u8 port)
{
	struct mlx4_eqe eqe;


	if (dev->persist->num_vfs < slave)
		return 0;
	memset(&eqe, 0, sizeof eqe);

	eqe.type = MLX4_EVENT_TYPE_PORT_MNG_CHG_EVENT;
	eqe.subtype = MLX4_DEV_PMC_SUBTYPE_GUID_INFO;
	eqe.event.port_mgmt_change.port = mlx4_phys_to_slave_port(dev, slave, port);

	return mlx4_GEN_EQE(dev, slave, &eqe);
}
