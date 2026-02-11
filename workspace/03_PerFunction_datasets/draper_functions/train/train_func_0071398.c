fm10k_add_vxlan_port(struct net_device *dev,
				 sa_family_t sa_family, __be16 port) {
	struct fm10k_intfc *interface = netdev_priv(dev);
	struct fm10k_vxlan_port *vxlan_port;


	if (interface->hw.mac.type != fm10k_mac_pf)
		return;


	fm10k_vxlan_port_for_each(vxlan_port, interface) {
		if ((vxlan_port->port == port) &&
		    (vxlan_port->sa_family == sa_family)) {
			list_del(&vxlan_port->list);
			goto insert_tail;
		}
	}


	vxlan_port = kmalloc(sizeof(*vxlan_port), GFP_ATOMIC);
	if (!vxlan_port)
		return;
	vxlan_port->port = port;
	vxlan_port->sa_family = sa_family;

insert_tail:

	list_add_tail(&vxlan_port->list, &interface->vxlan_port);

	fm10k_restore_vxlan_port(interface);
}
