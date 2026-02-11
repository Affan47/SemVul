_mv88e6xxx_vtu_stu_data_read(struct dsa_switch *ds,
					struct mv88e6xxx_vtu_stu_entry *entry,
					unsigned int nibble_offset)
{
	struct mv88e6xxx_priv_state *ps = ds_to_priv(ds);
	u16 regs[3];
	int i;
	int ret;

	for (i = 0; i < 3; ++i) {
		ret = _mv88e6xxx_reg_read(ds, REG_GLOBAL,
					  GLOBAL_VTU_DATA_0_3 + i);
		if (ret < 0)
			return ret;

		regs[i] = ret;
	}

	for (i = 0; i < ps->num_ports; ++i) {
		unsigned int shift = (i % 4) * 4 + nibble_offset;
		u16 reg = regs[i / 4];

		entry->data[i] = (reg >> shift) & GLOBAL_VTU_STU_DATA_MASK;
	}

	return 0;
}
