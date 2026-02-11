vxlan_fdb_delete(struct ndmsg *ndm, struct nlattr *tb[],
			    struct net_device *dev,
			    const unsigned char *addr, u16 vid)
{
	struct vxlan_dev *vxlan = netdev_priv(dev);
	struct vxlan_fdb *f;
	struct vxlan_rdst *rd = NULL;
	union vxlan_addr ip;
	__be16 port;
	u32 vni, ifindex;
	int err;

	err = vxlan_fdb_parse(tb, vxlan, &ip, &port, &vni, &ifindex);
	if (err)
		return err;

	err = -ENOENT;

	spin_lock_bh(&vxlan->hash_lock);
	f = vxlan_find_mac(vxlan, addr);
	if (!f)
		goto out;

	if (!vxlan_addr_any(&ip)) {
		rd = vxlan_fdb_find_rdst(f, &ip, port, vni, ifindex);
		if (!rd)
			goto out;
	}

	err = 0;


	if (rd && !list_is_singular(&f->remotes)) {
		list_del_rcu(&rd->list);
		vxlan_fdb_notify(vxlan, f, rd, RTM_DELNEIGH);
		kfree_rcu(rd, rcu);
		goto out;
	}

	vxlan_fdb_destroy(vxlan, f);

out:
	spin_unlock_bh(&vxlan->hash_lock);

	return err;
}
