cyapa_gen3_show_baseline(struct device *dev,
				   struct device_attribute *attr, char *buf)
{
	struct cyapa *cyapa = dev_get_drvdata(dev);
	int max_baseline, min_baseline;
	int tries;
	int ret;

	ret = cyapa_read_byte(cyapa, CYAPA_CMD_DEV_STATUS);
	if (ret < 0) {
		dev_err(dev, "Error reading dev status. err = %d\n", ret);
		goto out;
	}
	if ((ret & CYAPA_DEV_NORMAL) != CYAPA_DEV_NORMAL) {
		dev_warn(dev, "Trackpad device is busy. device state = 0x%x\n",
			 ret);
		ret = -EAGAIN;
		goto out;
	}

	ret = cyapa_write_byte(cyapa, CYAPA_CMD_SOFT_RESET,
			       OP_REPORT_BASELINE_MASK);
	if (ret < 0) {
		dev_err(dev, "Failed to send report baseline command. %d\n",
			ret);
		goto out;
	}

	tries = 3;
	do {
		usleep_range(10000, 20000);

		ret = cyapa_read_byte(cyapa, CYAPA_CMD_DEV_STATUS);
		if (ret < 0) {
			dev_err(dev, "Error reading dev status. err = %d\n",
				ret);
			goto out;
		}
		if ((ret & CYAPA_DEV_NORMAL) == CYAPA_DEV_NORMAL)
			break;
	} while (--tries);

	if (tries == 0) {
		dev_err(dev, "Device timed out going to Normal state.\n");
		ret = -ETIMEDOUT;
		goto out;
	}

	ret = cyapa_read_byte(cyapa, CYAPA_CMD_MAX_BASELINE);
	if (ret < 0) {
		dev_err(dev, "Failed to read max baseline. err = %d\n", ret);
		goto out;
	}
	max_baseline = ret;

	ret = cyapa_read_byte(cyapa, CYAPA_CMD_MIN_BASELINE);
	if (ret < 0) {
		dev_err(dev, "Failed to read min baseline. err = %d\n", ret);
		goto out;
	}
	min_baseline = ret;

	dev_dbg(dev, "Baseline report successful. Max: %d Min: %d\n",
		max_baseline, min_baseline);
	ret = scnprintf(buf, PAGE_SIZE, "%d %d\n", max_baseline, min_baseline);

out:
	return ret;
}
