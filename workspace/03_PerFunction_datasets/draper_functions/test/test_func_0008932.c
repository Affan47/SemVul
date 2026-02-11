mlx4_ib_tunnels_update(struct mlx4_ib_dev *dev, int slave,
				  int port, int do_init)
{
	int ret = 0;

	if (!do_init) {
		clean_vf_mcast(&dev->sriov.demux[port - 1], slave);

		if (slave == mlx4_master_func_num(dev->dev))
			destroy_pv_resources(dev, slave, port,
					     dev->sriov.sqps[port - 1], 1);

		destroy_pv_resources(dev, slave, port,
				     dev->sriov.demux[port - 1].tun[slave], 1);
		return 0;
	}


	ret = create_pv_resources(&dev->ib_dev, slave, port, 1,
				  dev->sriov.demux[port - 1].tun[slave]);


	if (!ret && slave == mlx4_master_func_num(dev->dev))
		ret = create_pv_resources(&dev->ib_dev, slave, port, 0,
					  dev->sriov.sqps[port - 1]);
	return ret;
}
