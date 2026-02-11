mlxsw_sp_port_add_vid(struct net_device *dev, __be16 __always_unused proto,
			  u16 vid)
{
	struct mlxsw_sp_port *mlxsw_sp_port = netdev_priv(dev);
	struct mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	char *sftr_pl;
	int err;


	if (!vid)
		return 0;

	if (test_bit(vid, mlxsw_sp_port->active_vfids)) {
		netdev_warn(dev, "VID=%d already configured\n", vid);
		return 0;
	}

	if (!test_bit(vid, mlxsw_sp->active_vfids)) {
		err = mlxsw_sp_vfid_create(mlxsw_sp, vid);
		if (err) {
			netdev_err(dev, "Failed to create vFID=%d\n",
				   MLXSW_SP_VFID_BASE + vid);
			return err;
		}

		sftr_pl = kmalloc(MLXSW_REG_SFTR_LEN, GFP_KERNEL);
		if (!sftr_pl) {
			err = -ENOMEM;
			goto err_flood_table_alloc;
		}
		mlxsw_reg_sftr_pack(sftr_pl, 0, vid,
				    MLXSW_REG_SFGC_TABLE_TYPE_FID, 0,
				    MLXSW_PORT_CPU_PORT, true);
		err = mlxsw_reg_write(mlxsw_sp->core, MLXSW_REG(sftr), sftr_pl);
		kfree(sftr_pl);
		if (err) {
			netdev_err(dev, "Failed to configure flood table\n");
			goto err_flood_table_config;
		}
	}


	if (!mlxsw_sp_port->nr_vfids) {
		err = mlxsw_sp_port_vp_mode_trans(mlxsw_sp_port);
		if (err) {
			netdev_err(dev, "Failed to set to Virtual mode\n");
			return err;
		}
	}

	err = mlxsw_sp_port_vid_to_fid_set(mlxsw_sp_port,
					   MLXSW_REG_SVFA_MT_PORT_VID_TO_FID,
					   true, MLXSW_SP_VFID_BASE + vid, vid);
	if (err) {
		netdev_err(dev, "Failed to map {Port, VID=%d} to vFID=%d\n",
			   vid, MLXSW_SP_VFID_BASE + vid);
		goto err_port_vid_to_fid_set;
	}

	err = mlxsw_sp_port_vid_learning_set(mlxsw_sp_port, vid, false);
	if (err) {
		netdev_err(dev, "Failed to disable learning for VID=%d\n", vid);
		goto err_port_vid_learning_set;
	}

	err = mlxsw_sp_port_vlan_set(mlxsw_sp_port, vid, vid, true, false);
	if (err) {
		netdev_err(dev, "Failed to set VLAN membership for VID=%d\n",
			   vid);
		goto err_port_add_vid;
	}

	err = mlxsw_sp_port_stp_state_set(mlxsw_sp_port, vid,
					  MLXSW_REG_SPMS_STATE_FORWARDING);
	if (err) {
		netdev_err(dev, "Failed to set STP state for VID=%d\n", vid);
		goto err_port_stp_state_set;
	}

	mlxsw_sp_port->nr_vfids++;
	set_bit(vid, mlxsw_sp_port->active_vfids);

	return 0;

err_flood_table_config:
err_flood_table_alloc:
	mlxsw_sp_vfid_destroy(mlxsw_sp, vid);
	return err;

err_port_stp_state_set:
	mlxsw_sp_port_vlan_set(mlxsw_sp_port, vid, vid, false, false);
err_port_add_vid:
	mlxsw_sp_port_vid_learning_set(mlxsw_sp_port, vid, true);
err_port_vid_learning_set:
	mlxsw_sp_port_vid_to_fid_set(mlxsw_sp_port,
				     MLXSW_REG_SVFA_MT_PORT_VID_TO_FID, false,
				     MLXSW_SP_VFID_BASE + vid, vid);
err_port_vid_to_fid_set:
	mlxsw_sp_port_vlan_mode_trans(mlxsw_sp_port);
	return err;
}
