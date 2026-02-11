can_update_state_error_stats(struct net_device *dev,
					 enum can_state new_state)
{
	struct can_priv *priv = netdev_priv(dev);

	if (new_state <= priv->state)
		return;

	switch (new_state) {
	case CAN_STATE_ERROR_WARNING:
		priv->can_stats.error_warning++;
		break;
	case CAN_STATE_ERROR_PASSIVE:
		priv->can_stats.error_passive++;
		break;
	case CAN_STATE_BUS_OFF:
		priv->can_stats.bus_off++;
		break;
	default:
		break;
	}
}
