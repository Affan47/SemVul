handle_bonded_port_state_event(struct work_struct *work)
{
	struct ib_event_work *ew =
		container_of(work, struct ib_event_work, work);
	struct mlx4_ib_dev *ibdev = ew->ib_dev;
	enum ib_port_state bonded_port_state = IB_PORT_NOP;
	int i;
	struct ib_event ibev;

	kfree(ew);
	spin_lock_bh(&ibdev->iboe.lock);
	for (i = 0; i < MLX4_MAX_PORTS; ++i) {
		struct net_device *curr_netdev = ibdev->iboe.netdevs[i];
		enum ib_port_state curr_port_state;

		if (!curr_netdev)
			continue;

		curr_port_state =
			(netif_running(curr_netdev) &&
			 netif_carrier_ok(curr_netdev)) ?
			IB_PORT_ACTIVE : IB_PORT_DOWN;

		bonded_port_state = (bonded_port_state != IB_PORT_ACTIVE) ?
			curr_port_state : IB_PORT_ACTIVE;
	}
	spin_unlock_bh(&ibdev->iboe.lock);

	ibev.device = &ibdev->ib_dev;
	ibev.element.port_num = 1;
	ibev.event = (bonded_port_state == IB_PORT_ACTIVE) ?
		IB_EVENT_PORT_ACTIVE : IB_EVENT_PORT_ERR;

	ib_dispatch_event(&ibev);
}
