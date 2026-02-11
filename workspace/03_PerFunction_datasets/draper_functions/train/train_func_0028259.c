__set_phy_state(struct exynos_mipi_video_phy *state,
			enum exynos_mipi_phy_id id, unsigned int on)
{
	const unsigned int offset = EXYNOS4_MIPI_PHY_CONTROL(id / 2);
	void __iomem *addr;
	u32 val, reset;

	if (is_mipi_dsim_phy_id(id))
		reset = EXYNOS4_MIPI_PHY_MRESETN;
	else
		reset = EXYNOS4_MIPI_PHY_SRESETN;

	spin_lock(&state->slock);

	if (!IS_ERR(state->regmap)) {
		regmap_read(state->regmap, offset, &val);
		if (on)
			val |= reset;
		else
			val &= ~reset;
		regmap_write(state->regmap, offset, val);
		if (on)
			val |= EXYNOS4_MIPI_PHY_ENABLE;
		else if (!(val & EXYNOS4_MIPI_PHY_RESET_MASK))
			val &= ~EXYNOS4_MIPI_PHY_ENABLE;
		regmap_write(state->regmap, offset, val);
	} else {
		addr = state->regs + EXYNOS_MIPI_PHY_CONTROL(id / 2);

		val = readl(addr);
		if (on)
			val |= reset;
		else
			val &= ~reset;
		writel(val, addr);

		if (on)
			val |= EXYNOS4_MIPI_PHY_ENABLE;
		else if (!(val & EXYNOS4_MIPI_PHY_RESET_MASK))
			val &= ~EXYNOS4_MIPI_PHY_ENABLE;

		writel(val, addr);
	}

	spin_unlock(&state->slock);
	return 0;
}
