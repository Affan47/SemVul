hpav_dump_write_mac_memory_confirm(void *buf, int len, struct ether_header *UNUSED(hdr))
{
	int avail = len;
	struct write_mac_memory_confirm *mm = buf;

	switch (mm->mstatus) {
	case 0x00:
		faifa_printf(out_stream, "Status: Succes\n");
		break;
	case 0x10:
		faifa_printf(out_stream, "Status: Invalid address\n");
		goto out;
		break;
	case 0x14:
		faifa_printf(out_stream, "Status: Invalid length\n");
		goto out;
		break;
	}
	faifa_printf(out_stream, "Address: 0x%08lx\n", (long unsigned int)(mm->address));
	faifa_printf(out_stream, "Length: 0x%08lx\n", (long unsigned int)(mm->length));
out:
	avail -= sizeof(*mm);

	return (len - avail);
}
