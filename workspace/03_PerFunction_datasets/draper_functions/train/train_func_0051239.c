btc_apply_voltage_dependency_rules(struct radeon_clock_voltage_dependency_table *table,
					u32 clock, u16 max_voltage, u16 *voltage)
{
	u32 i;

	if ((table == NULL) || (table->count == 0))
		return;

	for (i= 0; i < table->count; i++) {
		if (clock <= table->entries[i].clk) {
			if (*voltage < table->entries[i].v)
				*voltage = (u16)((table->entries[i].v < max_voltage) ?
						  table->entries[i].v : max_voltage);
			return;
		}
	}

	*voltage = (*voltage > max_voltage) ? *voltage : max_voltage;
}
