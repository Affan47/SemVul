probe_for_cmd640_pci1(void)
{
	__get_cmd640_reg = get_cmd640_reg_pci1;
	__put_cmd640_reg = put_cmd640_reg_pci1;
	for (cmd640_key = 0x80000000;
	     cmd640_key <= 0x8000f800;
	     cmd640_key += 0x800) {
		if (match_pci_cmd640_device())
			return 1;
	}
	return 0;
}
