_is_dellssd_cntrl(const char *path)
{
	uint64_t vdr, dev, svdr, cls;

	vdr = get_uint64(path, 0, "vendor");
	dev = get_uint64(path, 0, "device");
	cls = get_uint64(path, 0, "class");
	svdr = get_uint64(path, 0, "subsystem_vendor");

	return ((vdr == 0x1344L && dev == 0x5150L) ||
	        (svdr == 0x1028 && cls == 0x10802));
}
