xen_apic_write(u32 reg, u32 val)
{
	if (reg == APIC_LVTPC) {
		(void)pmu_apic_update(reg);
		return;
	}


	WARN(1,"register: %x, value: %x\n", reg, val);
}
