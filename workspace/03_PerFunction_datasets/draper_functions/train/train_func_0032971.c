mlxsw_sx_pude_event_func(const struct mlxsw_reg_info *reg,
				     char *pude_pl, void *priv)
{
	struct mlxsw_sx *mlxsw_sx = priv;
	struct mlxsw_sx_port *mlxsw_sx_port;
	enum mlxsw_reg_pude_oper_status status;
	u8 local_port;

	local_port = mlxsw_reg_pude_local_port_get(pude_pl);
	mlxsw_sx_port = mlxsw_sx->ports[local_port];
	if (!mlxsw_sx_port) {
		dev_warn(mlxsw_sx->bus_info->dev, "Port %d: Link event received for non-existent port\n",
			 local_port);
		return;
	}

	status = mlxsw_reg_pude_oper_status_get(pude_pl);
	if (status == MLXSW_PORT_OPER_STATUS_UP) {
		netdev_info(mlxsw_sx_port->dev, "link up\n");
		netif_carrier_on(mlxsw_sx_port->dev);
	} else {
		netdev_info(mlxsw_sx_port->dev, "link down\n");
		netif_carrier_off(mlxsw_sx_port->dev);
	}
}
