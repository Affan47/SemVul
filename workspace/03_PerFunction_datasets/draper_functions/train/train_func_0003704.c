_mv88e6xxx_vlan_init(struct dsa_switch *ds, u16 vid,
				struct mv88e6xxx_vtu_stu_entry *entry)
{
	struct mv88e6xxx_priv_state *ps = ds_to_priv(ds);
	struct mv88e6xxx_vtu_stu_entry vlan = {
		.valid = true,
		.vid = vid,
		.fid = vid,
	};
	int i;


	for (i = 0; i < ps->num_ports; ++i)
		vlan.data[i] = dsa_is_cpu_port(ds, i) || dsa_is_dsa_port(ds, i)
			? GLOBAL_VTU_DATA_MEMBER_TAG_UNMODIFIED
			: GLOBAL_VTU_DATA_MEMBER_TAG_NON_MEMBER;

	if (mv88e6xxx_6097_family(ds) || mv88e6xxx_6165_family(ds) ||
	    mv88e6xxx_6351_family(ds) || mv88e6xxx_6352_family(ds)) {
		struct mv88e6xxx_vtu_stu_entry vstp;
		int err;


		vlan.sid = 0;
		err = _mv88e6xxx_stu_getnext(ds, GLOBAL_VTU_SID_MASK, &vstp);
		if (err)
			return err;

		if (vstp.sid != vlan.sid || !vstp.valid) {
			memset(&vstp, 0, sizeof(vstp));
			vstp.valid = true;
			vstp.sid = vlan.sid;

			err = _mv88e6xxx_stu_loadpurge(ds, &vstp);
			if (err)
				return err;
		}


		err = _mv88e6xxx_atu_flush(ds, vlan.fid, true);
		if (err)
			return err;
	}

	*entry = vlan;
	return 0;
}
