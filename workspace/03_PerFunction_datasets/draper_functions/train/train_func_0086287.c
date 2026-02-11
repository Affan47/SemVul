__get_link_speed(struct port *port)
{
	struct slave *slave = port->slave;
	u16 speed;


	if (slave->link != BOND_LINK_UP)
		speed = 0;
	else {
		switch (slave->speed) {
		case SPEED_10:
			speed = AD_LINK_SPEED_10MBPS;
			break;

		case SPEED_100:
			speed = AD_LINK_SPEED_100MBPS;
			break;

		case SPEED_1000:
			speed = AD_LINK_SPEED_1000MBPS;
			break;

		case SPEED_2500:
			speed = AD_LINK_SPEED_2500MBPS;
			break;

		case SPEED_5000:
			speed = AD_LINK_SPEED_5000MBPS;
			break;

		case SPEED_10000:
			speed = AD_LINK_SPEED_10000MBPS;
			break;

		case SPEED_20000:
			speed = AD_LINK_SPEED_20000MBPS;
			break;

		case SPEED_25000:
			speed = AD_LINK_SPEED_25000MBPS;
			break;

		case SPEED_40000:
			speed = AD_LINK_SPEED_40000MBPS;
			break;

		case SPEED_50000:
			speed = AD_LINK_SPEED_50000MBPS;
			break;

		case SPEED_56000:
			speed = AD_LINK_SPEED_56000MBPS;
			break;

		case SPEED_100000:
			speed = AD_LINK_SPEED_100000MBPS;
			break;

		default:

			speed = 0;
			break;
		}
	}

	netdev_dbg(slave->bond->dev, "Port %d Received link speed %d update from adapter\n",
		   port->actor_port_number, speed);
	return speed;
}
