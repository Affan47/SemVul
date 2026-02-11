mlxsw_sp_port_remove(struct mlxsw_sp *mlxsw_sp, u8 local_port)
{
	struct mlxsw_sp_port *mlxsw_sp_port = mlxsw_sp->ports[local_port];

	if (!mlxsw_sp_port)
		return;
	mlxsw_sp_port_kill_vid(mlxsw_sp_port->dev, 0, 1);
	unregister_netdev(mlxsw_sp_port->dev);
	mlxsw_sp_port_switchdev_fini(mlxsw_sp_port);
	free_percpu(mlxsw_sp_port->pcpu_stats);
	free_netdev(mlxsw_sp_port->dev);
}
