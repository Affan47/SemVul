__ipoib_mcast_add(struct net_device *dev, struct ipoib_mcast *mcast)
{
	struct ipoib_dev_priv *priv = netdev_priv(dev);
	struct rb_node **n = &priv->multicast_tree.rb_node, *pn = NULL;

	while (*n) {
		struct ipoib_mcast *tmcast;
		int ret;

		pn = *n;
		tmcast = rb_entry(pn, struct ipoib_mcast, rb_node);

		ret = memcmp(mcast->mcmember.mgid.raw, tmcast->mcmember.mgid.raw,
			     sizeof (union ib_gid));
		if (ret < 0)
			n = &pn->rb_left;
		else if (ret > 0)
			n = &pn->rb_right;
		else
			return -EEXIST;
	}

	rb_link_node(&mcast->rb_node, pn, n);
	rb_insert_color(&mcast->rb_node, &priv->multicast_tree);

	return 0;
}
