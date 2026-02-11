wm5100_runtime_suspend(struct device *dev)
{
	struct wm5100_priv *wm5100 = dev_get_drvdata(dev);

	regcache_cache_only(wm5100->regmap, true);
	regcache_mark_dirty(wm5100->regmap);
	if (wm5100->pdata.ldo_ena)
		gpio_set_value_cansleep(wm5100->pdata.ldo_ena, 0);
	regulator_bulk_disable(ARRAY_SIZE(wm5100->core_supplies),
			       wm5100->core_supplies);

	return 0;
}
