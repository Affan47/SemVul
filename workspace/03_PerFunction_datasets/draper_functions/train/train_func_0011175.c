__gate_commit(struct ccu_data *ccu, struct bcm_clk_gate *gate)
{
	u32 reg_val;
	u32 mask;
	bool enabled = false;

	BUG_ON(!gate_exists(gate));
	if (!gate_is_sw_controllable(gate))
		return true;

	reg_val = __ccu_read(ccu, gate->offset);


	if (gate_is_hw_controllable(gate)) {
		mask = (u32)1 << gate->hw_sw_sel_bit;
		if (gate_is_sw_managed(gate))
			reg_val |= mask;
		else
			reg_val &= ~mask;
	}


	mask = (u32)1 << gate->en_bit;
	if (gate_is_sw_managed(gate) && (enabled = gate_is_enabled(gate)) &&
			!gate_is_no_disable(gate))
		reg_val |= mask;
	else
		reg_val &= ~mask;

	__ccu_write(ccu, gate->offset, reg_val);


	if (!gate_is_sw_managed(gate))
		return true;


	return __ccu_wait_bit(ccu, gate->offset, gate->status_bit, enabled);
}
