wm_coeff_read_control(struct wm_coeff_ctl *ctl,
				 void *buf, size_t len)
{
	struct wm_adsp_alg_region *alg_region = &ctl->alg_region;
	const struct wm_adsp_region *mem;
	struct wm_adsp *dsp = ctl->dsp;
	void *scratch;
	int ret;
	unsigned int reg;

	mem = wm_adsp_find_region(dsp, alg_region->type);
	if (!mem) {
		adsp_err(dsp, "No base for region %x\n",
			 alg_region->type);
		return -EINVAL;
	}

	reg = ctl->alg_region.base + ctl->offset;
	reg = wm_adsp_region_to_reg(mem, reg);

	scratch = kmalloc(ctl->len, GFP_KERNEL | GFP_DMA);
	if (!scratch)
		return -ENOMEM;

	ret = regmap_raw_read(dsp->regmap, reg, scratch, ctl->len);
	if (ret) {
		adsp_err(dsp, "Failed to read %zu bytes from %x: %d\n",
			 ctl->len, reg, ret);
		kfree(scratch);
		return ret;
	}
	adsp_dbg(dsp, "Read %zu bytes from %x\n", ctl->len, reg);

	memcpy(buf, scratch, ctl->len);
	kfree(scratch);

	return 0;
}
