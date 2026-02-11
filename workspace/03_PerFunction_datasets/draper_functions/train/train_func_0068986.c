handle_lid_change_event(struct mlx4_ib_dev *dev, u8 port_num)
{
	mlx4_ib_dispatch_event(dev, port_num, IB_EVENT_LID_CHANGE);

	if (mlx4_is_master(dev->dev) && !dev->sriov.is_going_down)
		mlx4_gen_slaves_port_mgt_ev(dev->dev, port_num,
					    MLX4_EQ_PORT_INFO_LID_CHANGE_MASK);
}
