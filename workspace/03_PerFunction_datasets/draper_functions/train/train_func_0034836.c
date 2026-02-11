hme_set_settings(struct net_device *dev, struct ethtool_cmd *cmd)
{
	struct happy_meal *hp = netdev_priv(dev);


	if (cmd->autoneg != AUTONEG_ENABLE &&
	    cmd->autoneg != AUTONEG_DISABLE)
		return -EINVAL;
	if (cmd->autoneg == AUTONEG_DISABLE &&
	    ((ethtool_cmd_speed(cmd) != SPEED_100 &&
	      ethtool_cmd_speed(cmd) != SPEED_10) ||
	     (cmd->duplex != DUPLEX_HALF &&
	      cmd->duplex != DUPLEX_FULL)))
		return -EINVAL;


	spin_lock_irq(&hp->happy_lock);
	del_timer(&hp->happy_timer);
	happy_meal_begin_auto_negotiation(hp, hp->tcvregs, cmd);
	spin_unlock_irq(&hp->happy_lock);

	return 0;
}
