ipvlan_nl_fillinfo(struct sk_buff *skb,
			      const struct net_device *dev)
{
	struct ipvl_dev *ipvlan = netdev_priv(dev);
	struct ipvl_port *port = ipvlan_port_get_rtnl(ipvlan->phy_dev);
	int ret = -EINVAL;

	if (!port)
		goto err;

	ret = -EMSGSIZE;
	if (nla_put_u16(skb, IFLA_IPVLAN_MODE, port->mode))
		goto err;

	return 0;

err:
	return ret;
}
