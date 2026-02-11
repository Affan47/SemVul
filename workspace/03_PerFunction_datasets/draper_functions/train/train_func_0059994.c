exynos4210_tmu_read(struct exynos_tmu_data *data)
{
	int ret = readb(data->base + EXYNOS_TMU_REG_CURRENT_TEMP);


	return (ret < 75 || ret > 175) ? -ENODATA : ret;
}
