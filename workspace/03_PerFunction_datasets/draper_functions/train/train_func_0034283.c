s5k5baf_fw_parse(struct device *dev, struct s5k5baf_fw **fw,
			    size_t count, const __le16 *data)
{
	struct s5k5baf_fw *f;
	u16 *d, i, *end;
	int ret;

	if (count < S5K5BAG_FW_TAG_LEN + 1) {
		dev_err(dev, "firmware file too short (%zu)\n", count);
		return -EINVAL;
	}

	ret = memcmp(data, S5K5BAF_FW_TAG, S5K5BAG_FW_TAG_LEN * sizeof(u16));
	if (ret != 0) {
		dev_err(dev, "invalid firmware magic number\n");
		return -EINVAL;
	}

	data += S5K5BAG_FW_TAG_LEN;
	count -= S5K5BAG_FW_TAG_LEN;

	d = devm_kzalloc(dev, count * sizeof(u16), GFP_KERNEL);
	if (!d)
		return -ENOMEM;

	for (i = 0; i < count; ++i)
		d[i] = le16_to_cpu(data[i]);

	f = (struct s5k5baf_fw *)d;
	if (count < 1 + 2 * f->count) {
		dev_err(dev, "invalid firmware header (count=%d size=%zu)\n",
			f->count, 2 * (count + S5K5BAG_FW_TAG_LEN));
		return -EINVAL;
	}
	end = d + count;
	d += 1 + 2 * f->count;

	for (i = 0; i < f->count; ++i) {
		if (f->seq[i].offset + d <= end)
			continue;
		dev_err(dev, "invalid firmware header (seq=%d)\n", i);
		return -EINVAL;
	}

	*fw = f;

	return 0;
}
