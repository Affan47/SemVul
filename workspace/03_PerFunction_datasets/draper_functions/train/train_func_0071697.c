ib_mad_port_close(struct ib_device *device, int port_num)
{
	struct ib_mad_port_private *port_priv;
	unsigned long flags;

	spin_lock_irqsave(&ib_mad_port_list_lock, flags);
	port_priv = __ib_get_mad_port(device, port_num);
	if (port_priv == NULL) {
		spin_unlock_irqrestore(&ib_mad_port_list_lock, flags);
		dev_err(&device->dev, "Port %d not found\n", port_num);
		return -ENODEV;
	}
	list_del_init(&port_priv->port_list);
	spin_unlock_irqrestore(&ib_mad_port_list_lock, flags);

	destroy_workqueue(port_priv->wq);
	destroy_mad_qp(&port_priv->qp_info[1]);
	destroy_mad_qp(&port_priv->qp_info[0]);
	ib_dealloc_pd(port_priv->pd);
	ib_destroy_cq(port_priv->cq);
	cleanup_recv_queue(&port_priv->qp_info[1]);
	cleanup_recv_queue(&port_priv->qp_info[0]);


	kfree(port_priv);

	return 0;
}
