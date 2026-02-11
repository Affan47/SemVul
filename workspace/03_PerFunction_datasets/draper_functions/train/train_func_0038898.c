intel_get_register_map(uint32_t devid)
{
	struct intel_register_map map;
	const int gen = intel_gen(devid);

	if (gen >= 6) {
		map.map = gen6_gt_register_map;
		map.top = 0x180000;
	} else if (IS_BROADWATER(devid) || IS_CRESTLINE(devid)) {
		map.map = gen_bwcl_register_map;
		map.top = 0x80000;
	} else if (gen >= 4) {
		map.map = gen4_register_map;
		map.top = 0x80000;
	} else {
		fprintf(stderr, "Gen2/3 Ranges are not supported. Please use "
			"unsafe access.");
	}

	map.alignment_mask = 0x3;

	return map;
}
