as3711_backlight_parse_dt(struct device *dev)
{
	struct as3711_bl_pdata *pdata = dev_get_platdata(dev);
	struct device_node *bl =
		of_find_node_by_name(dev->parent->of_node, "backlight"), *fb;
	int ret;

	if (!bl) {
		dev_dbg(dev, "backlight node not found\n");
		return -ENODEV;
	}

	fb = of_parse_phandle(bl, "su1-dev", 0);
	if (fb) {
		pdata->su1_fb = fb->full_name;

		ret = of_property_read_u32(bl, "su1-max-uA", &pdata->su1_max_uA);
		if (pdata->su1_max_uA <= 0)
			ret = -EINVAL;
		if (ret < 0)
			return ret;
	}

	fb = of_parse_phandle(bl, "su2-dev", 0);
	if (fb) {
		int count = 0;

		pdata->su2_fb = fb->full_name;

		ret = of_property_read_u32(bl, "su2-max-uA", &pdata->su2_max_uA);
		if (pdata->su2_max_uA <= 0)
			ret = -EINVAL;
		if (ret < 0)
			return ret;

		if (of_find_property(bl, "su2-feedback-voltage", NULL)) {
			pdata->su2_feedback = AS3711_SU2_VOLTAGE;
			count++;
		}
		if (of_find_property(bl, "su2-feedback-curr1", NULL)) {
			pdata->su2_feedback = AS3711_SU2_CURR1;
			count++;
		}
		if (of_find_property(bl, "su2-feedback-curr2", NULL)) {
			pdata->su2_feedback = AS3711_SU2_CURR2;
			count++;
		}
		if (of_find_property(bl, "su2-feedback-curr3", NULL)) {
			pdata->su2_feedback = AS3711_SU2_CURR3;
			count++;
		}
		if (of_find_property(bl, "su2-feedback-curr-auto", NULL)) {
			pdata->su2_feedback = AS3711_SU2_CURR_AUTO;
			count++;
		}
		if (count != 1)
			return -EINVAL;

		count = 0;
		if (of_find_property(bl, "su2-fbprot-lx-sd4", NULL)) {
			pdata->su2_fbprot = AS3711_SU2_LX_SD4;
			count++;
		}
		if (of_find_property(bl, "su2-fbprot-gpio2", NULL)) {
			pdata->su2_fbprot = AS3711_SU2_GPIO2;
			count++;
		}
		if (of_find_property(bl, "su2-fbprot-gpio3", NULL)) {
			pdata->su2_fbprot = AS3711_SU2_GPIO3;
			count++;
		}
		if (of_find_property(bl, "su2-fbprot-gpio4", NULL)) {
			pdata->su2_fbprot = AS3711_SU2_GPIO4;
			count++;
		}
		if (count != 1)
			return -EINVAL;

		count = 0;
		if (of_find_property(bl, "su2-auto-curr1", NULL)) {
			pdata->su2_auto_curr1 = true;
			count++;
		}
		if (of_find_property(bl, "su2-auto-curr2", NULL)) {
			pdata->su2_auto_curr2 = true;
			count++;
		}
		if (of_find_property(bl, "su2-auto-curr3", NULL)) {
			pdata->su2_auto_curr3 = true;
			count++;
		}


		if (!count ^ (pdata->su2_feedback != AS3711_SU2_CURR_AUTO))
			return -EINVAL;
	}

	return 0;
}
