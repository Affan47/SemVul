mlxsw_sp_port_obj_dump(struct net_device *dev,
				  struct switchdev_obj *obj,
				  switchdev_obj_dump_cb_t *cb)
{
	struct mlxsw_sp_port *mlxsw_sp_port = netdev_priv(dev);
	int err = 0;

	switch (obj->id) {
	case SWITCHDEV_OBJ_ID_PORT_VLAN:
		err = mlxsw_sp_port_vlan_dump(mlxsw_sp_port,
					      SWITCHDEV_OBJ_PORT_VLAN(obj), cb);
		break;
	case SWITCHDEV_OBJ_ID_PORT_FDB:
		err = mlxsw_sp_port_fdb_dump(mlxsw_sp_port,
					     SWITCHDEV_OBJ_PORT_FDB(obj), cb);
		break;
	default:
		err = -EOPNOTSUPP;
		break;
	}

	return err;
}
