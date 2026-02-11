wl12xx_sdio_raw_write(struct device *child, int addr,
					      void *buf, size_t len, bool fixed)
{
	int ret;
	struct wl12xx_sdio_glue *glue = dev_get_drvdata(child->parent);
	struct sdio_func *func = dev_to_sdio_func(glue->dev);

	sdio_claim_host(func);

	if (unlikely(dump)) {
		printk(KERN_DEBUG "wlcore_sdio: WRITE to 0x%04x\n", addr);
		print_hex_dump(KERN_DEBUG, "wlcore_sdio: WRITE ",
				DUMP_PREFIX_OFFSET, 16, 1,
				buf, len, false);
	}

	if (unlikely(addr == HW_ACCESS_ELP_CTRL_REG)) {
		sdio_f0_writeb(func, ((u8 *)buf)[0], addr, &ret);
		dev_dbg(child->parent, "sdio write 52 addr 0x%x, byte 0x%02x\n",
			addr, ((u8 *)buf)[0]);
	} else {
		dev_dbg(child->parent, "sdio write 53 addr 0x%x, %zu bytes\n",
			addr, len);

		if (fixed)
			ret = sdio_writesb(func, addr, buf, len);
		else
			ret = sdio_memcpy_toio(func, addr, buf, len);
	}

	sdio_release_host(func);

	if (WARN_ON(ret))
		dev_err(child->parent, "sdio write failed (%d)\n", ret);

	return ret;
}
