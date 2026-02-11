acpi_processor_ffh_cstate_probe_cpu(void *_cx)
{
	struct acpi_processor_cx *cx = _cx;
	long retval;
	unsigned int eax, ebx, ecx, edx;
	unsigned int edx_part;
	unsigned int cstate_type;
	unsigned int num_cstate_subtype;

	cpuid(CPUID_MWAIT_LEAF, &eax, &ebx, &ecx, &edx);


	cstate_type = ((cx->address >> MWAIT_SUBSTATE_SIZE) &
			MWAIT_CSTATE_MASK) + 1;
	edx_part = edx >> (cstate_type * MWAIT_SUBSTATE_SIZE);
	num_cstate_subtype = edx_part & MWAIT_SUBSTATE_MASK;

	retval = 0;

	if (num_cstate_subtype == 0) {
		pr_warn(FW_BUG "ACPI MWAIT C-state 0x%x not supported by HW (0x%x)\n", cx->address, edx_part);
		retval = -1;
		goto out;
	}


	if (!(ecx & CPUID5_ECX_EXTENSIONS_SUPPORTED) ||
	    !(ecx & CPUID5_ECX_INTERRUPT_BREAK)) {
		retval = -1;
		goto out;
	}

	if (!mwait_supported[cstate_type]) {
		mwait_supported[cstate_type] = 1;
		printk(KERN_DEBUG
			"Monitor-Mwait will be used to enter C-%d "
			"state\n", cx->type);
	}
	snprintf(cx->desc,
			ACPI_CX_DESC_LEN, "ACPI FFH INTEL MWAIT 0x%x",
			cx->address);
out:
	return retval;
}
