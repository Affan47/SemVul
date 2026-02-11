vmware_legacy_x2apic_available(void)
{
	uint32_t eax, ebx, ecx, edx;
	VMWARE_PORT(GETVCPU_INFO, eax, ebx, ecx, edx);
	return (eax & (1 << VMWARE_PORT_CMD_VCPU_RESERVED)) == 0 &&
	       (eax & (1 << VMWARE_PORT_CMD_LEGACY_X2APIC)) != 0;
}
