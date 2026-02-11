found_memconsole(void)
{
	unsigned int address;
	size_t length, cur;

	address = get_bios_ebda();
	if (!address) {
		pr_info("BIOS EBDA non-existent.\n");
		return false;
	}


	length = *(u8 *)phys_to_virt(address);
	length <<= 10;


	for (cur = 0; cur < length; cur++) {
		struct biosmemcon_ebda *hdr = phys_to_virt(address + cur);


		if (hdr->signature == BIOS_MEMCONSOLE_V1_MAGIC) {
			found_v1_header(hdr);
			return true;
		}


		if (hdr->signature == BIOS_MEMCONSOLE_V2_MAGIC) {
			found_v2_header(hdr);
			return true;
		}
	}

	pr_info("BIOS console EBDA structure not found!\n");
	return false;
}
