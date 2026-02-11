ipoib_mcast_leave(struct net_device *dev, struct ipoib_mcast *mcast)
{
	struct ipoib_dev_priv *priv = netdev_priv(dev);
	int ret = 0;

	if (test_and_clear_bit(IPOIB_MCAST_FLAG_BUSY, &mcast->flags))
		ipoib_warn(priv, "ipoib_mcast_leave on an in-flight join\n");

	if (!IS_ERR_OR_NULL(mcast->mc))
		ib_sa_free_multicast(mcast->mc);

	if (test_and_clear_bit(IPOIB_MCAST_FLAG_ATTACHED, &mcast->flags)) {
		ipoib_dbg_mcast(priv, "leaving MGID %pI6\n",
				mcast->mcmember.mgid.raw);


		ret = ib_detach_mcast(priv->qp, &mcast->mcmember.mgid,
				      be16_to_cpu(mcast->mcmember.mlid));
		if (ret)
			ipoib_warn(priv, "ib_detach_mcast failed (result = %d)\n", ret);
	} else if (!test_bit(IPOIB_MCAST_FLAG_SENDONLY, &mcast->flags))
		ipoib_dbg(priv, "leaving with no mcmember but not a "
			  "SENDONLY join\n");

	return 0;
}
