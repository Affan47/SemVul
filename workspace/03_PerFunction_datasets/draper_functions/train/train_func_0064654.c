mlxsw_core_bus_device_register(const struct mlxsw_bus_info *mlxsw_bus_info,
				   const struct mlxsw_bus *mlxsw_bus,
				   void *bus_priv)
{
	const char *device_kind = mlxsw_bus_info->device_kind;
	struct mlxsw_core *mlxsw_core;
	struct mlxsw_driver *mlxsw_driver;
	size_t alloc_size;
	int err;

	mlxsw_driver = mlxsw_core_driver_get(device_kind);
	if (!mlxsw_driver)
		return -EINVAL;
	alloc_size = sizeof(*mlxsw_core) + mlxsw_driver->priv_size;
	mlxsw_core = kzalloc(alloc_size, GFP_KERNEL);
	if (!mlxsw_core) {
		err = -ENOMEM;
		goto err_core_alloc;
	}

	INIT_LIST_HEAD(&mlxsw_core->rx_listener_list);
	INIT_LIST_HEAD(&mlxsw_core->event_listener_list);
	mlxsw_core->driver = mlxsw_driver;
	mlxsw_core->bus = mlxsw_bus;
	mlxsw_core->bus_priv = bus_priv;
	mlxsw_core->bus_info = mlxsw_bus_info;

	mlxsw_core->pcpu_stats =
		netdev_alloc_pcpu_stats(struct mlxsw_core_pcpu_stats);
	if (!mlxsw_core->pcpu_stats) {
		err = -ENOMEM;
		goto err_alloc_stats;
	}

	err = mlxsw_bus->init(bus_priv, mlxsw_core, mlxsw_driver->profile);
	if (err)
		goto err_bus_init;

	err = mlxsw_emad_init(mlxsw_core);
	if (err)
		goto err_emad_init;

	err = mlxsw_driver->init(mlxsw_core->driver_priv, mlxsw_core,
				 mlxsw_bus_info);
	if (err)
		goto err_driver_init;

	err = mlxsw_core_debugfs_init(mlxsw_core);
	if (err)
		goto err_debugfs_init;

	return 0;

err_debugfs_init:
	mlxsw_core->driver->fini(mlxsw_core->driver_priv);
err_driver_init:
	mlxsw_emad_fini(mlxsw_core);
err_emad_init:
	mlxsw_bus->fini(bus_priv);
err_bus_init:
	free_percpu(mlxsw_core->pcpu_stats);
err_alloc_stats:
	kfree(mlxsw_core);
err_core_alloc:
	mlxsw_core_driver_put(device_kind);
	return err;
}
