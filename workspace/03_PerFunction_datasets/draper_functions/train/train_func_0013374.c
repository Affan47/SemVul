hpav_dump_get_devices_attrs_confirm(void *buf, int len, struct ether_header *UNUSED(hdr))
{
	int avail = len;
	struct get_devices_attrs_confirm *mm = buf;

	switch (mm->status) {
	case 0x00:
		faifa_printf(out_stream, "Status: Success\n");
		break;
	case 0x01:
		faifa_printf(out_stream, "Status: Failure\n");
		goto out;
		break;
	case 0x02:
		faifa_printf(out_stream, "Status: Not supported\n");
		goto out;
		break;
	}
	faifa_printf(out_stream, "Cookie: %lu\n", (long unsigned int)(mm->cookie));
	faifa_printf(out_stream, "Report type: %s\n", (short unsigned int)(mm->rtype) ? "XML" : "Binary");
	faifa_printf(out_stream, "Size: %d\n", (unsigned int)(mm->size));
	faifa_printf(out_stream, "Hardware: %s\n", mm->fmt.hardware);
	faifa_printf(out_stream, "Software: %s\n", mm->fmt.software);
	faifa_printf(out_stream, "Major: %lu\n", (long unsigned int)(mm->fmt.major));
	faifa_printf(out_stream, "Minor: %lu\n", (long unsigned int)(mm->fmt.minor));
	faifa_printf(out_stream, "Subversion: %lu\n", (long unsigned int)(mm->fmt.subversion));
	faifa_printf(out_stream, "Build number: %lu\n", (long unsigned int)(mm->fmt.build_number));
	faifa_printf(out_stream, "Build date: %s\n", mm->fmt.build_date);
	faifa_printf(out_stream, "Release type: %s\n", mm->fmt.release_type);

out:
	avail -= sizeof(*mm);

	return (len - avail);
}
