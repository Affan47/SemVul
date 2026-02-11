of_unittest_apply_overlay_check(int overlay_nr, int unittest_nr,
		int before, int after, enum overlay_type ovtype)
{
	int ret;


	if (of_unittest_device_exists(unittest_nr, ovtype) != before) {
		unittest(0, "overlay @\"%s\" with device @\"%s\" %s\n",
				overlay_path(overlay_nr),
				unittest_path(unittest_nr, ovtype),
				!before ? "enabled" : "disabled");
		return -EINVAL;
	}

	ret = of_unittest_apply_overlay(overlay_nr, unittest_nr, NULL);
	if (ret != 0) {

		return ret;
	}


	if (of_unittest_device_exists(unittest_nr, ovtype) != after) {
		unittest(0, "overlay @\"%s\" failed to create @\"%s\" %s\n",
				overlay_path(overlay_nr),
				unittest_path(unittest_nr, ovtype),
				!after ? "enabled" : "disabled");
		return -EINVAL;
	}

	return 0;
}
