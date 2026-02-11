of_unittest_overlay_8(void)
{
	struct device_node *np;
	int ret, i, ov_id[2];
	int overlay_nr = 8, unittest_nr = 8;


	for (i = 0; i < 2; i++) {

		np = of_find_node_by_path(overlay_path(overlay_nr + i));
		if (np == NULL) {
			unittest(0, "could not find overlay node @\"%s\"\n",
					overlay_path(overlay_nr + i));
			return;
		}

		ret = of_overlay_create(np);
		if (ret < 0)  {
			unittest(0, "could not create overlay from \"%s\"\n",
					overlay_path(overlay_nr + i));
			return;
		}
		ov_id[i] = ret;
		of_unittest_track_overlay(ov_id[i]);
	}


	ret = of_overlay_destroy(ov_id[0]);
	if (ret == 0) {
		unittest(0, "overlay @\"%s\" was destroyed @\"%s\"\n",
				overlay_path(overlay_nr + 0),
				unittest_path(unittest_nr,
					PDEV_OVERLAY));
		return;
	}


	for (i = 1; i >= 0; i--) {
		ret = of_overlay_destroy(ov_id[i]);
		if (ret != 0) {
			unittest(0, "overlay @\"%s\" not destroyed @\"%s\"\n",
					overlay_path(overlay_nr + i),
					unittest_path(unittest_nr,
						PDEV_OVERLAY));
			return;
		}
		of_unittest_untrack_overlay(ov_id[i]);
	}

	unittest(1, "overlay test %d passed\n", 8);
}
