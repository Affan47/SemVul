mlxsw_sp_port_vlan_set(struct mlxsw_sp_port *mlxsw_sp_port, u16 vid_begin,
			   u16 vid_end, bool is_member, bool untagged)
{
	struct mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	char *spvm_pl;
	int err;

	spvm_pl = kmalloc(MLXSW_REG_SPVM_LEN, GFP_KERNEL);
	if (!spvm_pl)
		return -ENOMEM;

	mlxsw_reg_spvm_pack(spvm_pl, mlxsw_sp_port->local_port,	vid_begin,
			    vid_end, is_member, untagged);
	err = mlxsw_reg_write(mlxsw_sp->core, MLXSW_REG(spvm), spvm_pl);
	kfree(spvm_pl);
	return err;
}
