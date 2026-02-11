vxlan_group_used(struct vxlan_net *vn, struct vxlan_dev *dev)
{
	struct vxlan_dev *vxlan;
	unsigned short family = dev->default_dst.remote_ip.sa.sa_family;


	if (family == AF_INET && dev->vn4_sock &&
	    atomic_read(&dev->vn4_sock->refcnt) == 1)
		return false;
#if IS_ENABLED(CONFIG_IPV6)
	if (family == AF_INET6 && dev->vn6_sock &&
	    atomic_read(&dev->vn6_sock->refcnt) == 1)
		return false;
#endif

	list_for_each_entry(vxlan, &vn->vxlan_list, next) {
		if (!netif_running(vxlan->dev) || vxlan == dev)
			continue;

		if (family == AF_INET && vxlan->vn4_sock != dev->vn4_sock)
			continue;
#if IS_ENABLED(CONFIG_IPV6)
		if (family == AF_INET6 && vxlan->vn6_sock != dev->vn6_sock)
			continue;
#endif

		if (!vxlan_addr_equal(&vxlan->default_dst.remote_ip,
				      &dev->default_dst.remote_ip))
			continue;

		if (vxlan->default_dst.remote_ifindex !=
		    dev->default_dst.remote_ifindex)
			continue;

		return true;
	}

	return false;
}
