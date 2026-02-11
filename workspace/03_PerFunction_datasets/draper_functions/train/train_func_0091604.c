rdma_join_multicast(struct rdma_cm_id *id, struct sockaddr *addr,
			void *context)
{
	struct rdma_id_private *id_priv;
	struct cma_multicast *mc;
	int ret;

	id_priv = container_of(id, struct rdma_id_private, id);
	if (!cma_comp(id_priv, RDMA_CM_ADDR_BOUND) &&
	    !cma_comp(id_priv, RDMA_CM_ADDR_RESOLVED))
		return -EINVAL;

	mc = kmalloc(sizeof *mc, GFP_KERNEL);
	if (!mc)
		return -ENOMEM;

	memcpy(&mc->addr, addr, rdma_addr_size(addr));
	mc->context = context;
	mc->id_priv = id_priv;

	spin_lock(&id_priv->lock);
	list_add(&mc->list, &id_priv->mc_list);
	spin_unlock(&id_priv->lock);

	if (rdma_protocol_roce(id->device, id->port_num)) {
		kref_init(&mc->mcref);
		ret = cma_iboe_join_multicast(id_priv, mc);
	} else if (rdma_cap_ib_mcast(id->device, id->port_num))
		ret = cma_join_ib_multicast(id_priv, mc);
	else
		ret = -ENOSYS;

	if (ret) {
		spin_lock_irq(&id_priv->lock);
		list_del(&mc->list);
		spin_unlock_irq(&id_priv->lock);
		kfree(mc);
	}
	return ret;
}
