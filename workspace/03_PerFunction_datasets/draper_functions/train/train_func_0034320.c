enic_get_rxnfc(struct net_device *dev, struct ethtool_rxnfc *cmd,
			  u32 *rule_locs)
{
	struct enic *enic = netdev_priv(dev);
	int ret = 0;

	switch (cmd->cmd) {
	case ETHTOOL_GRXRINGS:
		cmd->data = enic->rq_count;
		break;
	case ETHTOOL_GRXCLSRLCNT:
		spin_lock_bh(&enic->rfs_h.lock);
		cmd->rule_cnt = enic->rfs_h.max - enic->rfs_h.free;
		cmd->data = enic->rfs_h.max;
		spin_unlock_bh(&enic->rfs_h.lock);
		break;
	case ETHTOOL_GRXCLSRLALL:
		spin_lock_bh(&enic->rfs_h.lock);
		ret = enic_grxclsrlall(enic, cmd, rule_locs);
		spin_unlock_bh(&enic->rfs_h.lock);
		break;
	case ETHTOOL_GRXCLSRULE:
		spin_lock_bh(&enic->rfs_h.lock);
		ret = enic_grxclsrule(enic, cmd);
		spin_unlock_bh(&enic->rfs_h.lock);
		break;
	default:
		ret = -EOPNOTSUPP;
		break;
	}

	return ret;
}
