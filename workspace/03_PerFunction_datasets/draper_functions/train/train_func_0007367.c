wusbhc_mmcie_create(struct wusbhc *wusbhc)
{
	u8 mmcies = wusbhc->mmcies_max;
	wusbhc->mmcie = kcalloc(mmcies, sizeof(wusbhc->mmcie[0]), GFP_KERNEL);
	if (wusbhc->mmcie == NULL)
		return -ENOMEM;
	mutex_init(&wusbhc->mmcie_mutex);
	return 0;
}
