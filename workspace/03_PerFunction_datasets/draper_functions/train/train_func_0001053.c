clear_local_APIC(void)
{
	int maxlvt;
	u32 v;


	if (!x2apic_mode && !apic_phys)
		return;

	maxlvt = lapic_get_maxlvt();


	if (maxlvt >= 3) {
		v = ERROR_APIC_VECTOR;
		apic_write(APIC_LVTERR, v | APIC_LVT_MASKED);
	}


	v = apic_read(APIC_LVTT);
	apic_write(APIC_LVTT, v | APIC_LVT_MASKED);
	v = apic_read(APIC_LVT0);
	apic_write(APIC_LVT0, v | APIC_LVT_MASKED);
	v = apic_read(APIC_LVT1);
	apic_write(APIC_LVT1, v | APIC_LVT_MASKED);
	if (maxlvt >= 4) {
		v = apic_read(APIC_LVTPC);
		apic_write(APIC_LVTPC, v | APIC_LVT_MASKED);
	}


#ifdef CONFIG_X86_THERMAL_VECTOR
	if (maxlvt >= 5) {
		v = apic_read(APIC_LVTTHMR);
		apic_write(APIC_LVTTHMR, v | APIC_LVT_MASKED);
	}
#endif
#ifdef CONFIG_X86_MCE_INTEL
	if (maxlvt >= 6) {
		v = apic_read(APIC_LVTCMCI);
		if (!(v & APIC_LVT_MASKED))
			apic_write(APIC_LVTCMCI, v | APIC_LVT_MASKED);
	}
#endif


	apic_write(APIC_LVTT, APIC_LVT_MASKED);
	apic_write(APIC_LVT0, APIC_LVT_MASKED);
	apic_write(APIC_LVT1, APIC_LVT_MASKED);
	if (maxlvt >= 3)
		apic_write(APIC_LVTERR, APIC_LVT_MASKED);
	if (maxlvt >= 4)
		apic_write(APIC_LVTPC, APIC_LVT_MASKED);


	if (lapic_is_integrated()) {
		if (maxlvt > 3)

			apic_write(APIC_ESR, 0);
		apic_read(APIC_ESR);
	}
}
