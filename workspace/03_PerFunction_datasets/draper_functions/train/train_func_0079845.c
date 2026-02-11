snd_intel8x0_inside_vm(struct pci_dev *pci)
{
	int result  = inside_vm;
	char *msg   = NULL;


	if (result >= 0) {
		msg = result ? "enable (forced) VM" : "disable (forced) VM";
		goto fini;
	}


	result = kvm_para_available();
#ifdef X86_FEATURE_HYPERVISOR
	result = result || boot_cpu_has(X86_FEATURE_HYPERVISOR);
#endif
	if (!result)
		goto fini;


	if (pci->subsystem_vendor == 0x1af4 &&
	    pci->subsystem_device == 0x1100) {

		msg = "enable KVM";
	} else if (pci->subsystem_vendor == 0x1ab8) {

		msg = "enable Parallels VM";
	} else {
		msg = "disable (unknown or VT-d) VM";
		result = 0;
	}

fini:
	if (msg != NULL)
		dev_info(&pci->dev, "%s optimization\n", msg);

	return result;
}
