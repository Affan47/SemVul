oaktrail_hdmi_i2c_gpio_fix(void)
{
	void __iomem *base;
	unsigned int gpio_base = 0xff12c000;
	int gpio_len = 0x1000;
	u32 temp;

	base = ioremap((resource_size_t)gpio_base, gpio_len);
	if (base == NULL) {
		DRM_ERROR("gpio ioremap fail\n");
		return;
	}

	temp = readl(base + 0x44);
	DRM_DEBUG_DRIVER("old gpio val %x\n", temp);
	writel((temp | 0x00000a00), (base +  0x44));
	temp = readl(base + 0x44);
	DRM_DEBUG_DRIVER("new gpio val %x\n", temp);

	iounmap(base);
}
