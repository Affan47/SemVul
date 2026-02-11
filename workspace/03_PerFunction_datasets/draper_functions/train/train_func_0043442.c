rapl_write_data_raw(struct rapl_domain *rd,
			enum rapl_primitives prim,
			unsigned long long value)
{
	u64 msr_val;
	u32 msr;
	struct rapl_primitive_info *rp = &rpi[prim];
	int cpu;

	cpu = find_active_cpu_on_package(rd->package_id);
	if (cpu < 0)
		return cpu;
	msr = rd->msrs[rp->id];
	if (rdmsrl_safe_on_cpu(cpu, msr, &msr_val)) {
		dev_dbg(&rd->power_zone.dev,
			"failed to read msr 0x%x on cpu %d\n", msr, cpu);
		return -EIO;
	}
	value = rapl_unit_xlate(rd, rd->package_id, rp->unit, value, 1);
	msr_val &= ~rp->mask;
	msr_val |= value << rp->shift;
	if (wrmsrl_safe_on_cpu(cpu, msr, msr_val)) {
		dev_dbg(&rd->power_zone.dev,
			"failed to write msr 0x%x on cpu %d\n", msr, cpu);
		return -EIO;
	}

	return 0;
}
