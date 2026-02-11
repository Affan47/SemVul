native_vm_disable_fault(enum vm_fault fault)
{
	if (fault < 0 || fault >= VM_FAULT_MAX)
		return;

	vm_fault_entries[fault].enabled = false;
}
