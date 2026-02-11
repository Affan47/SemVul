brcms_bcma_probe(struct bcma_device *pdev)
{
	struct brcms_info *wl;
	struct ieee80211_hw *hw;

	dev_info(&pdev->dev, "mfg %x core %x rev %d class %d irq %d\n",
		 pdev->id.manuf, pdev->id.id, pdev->id.rev, pdev->id.class,
		 pdev->irq);

	if ((pdev->id.manuf != BCMA_MANUF_BCM) ||
	    (pdev->id.id != BCMA_CORE_80211))
		return -ENODEV;

	hw = ieee80211_alloc_hw(sizeof(struct brcms_info), &brcms_ops);
	if (!hw) {
		pr_err("%s: ieee80211_alloc_hw failed\n", __func__);
		return -ENOMEM;
	}

	SET_IEEE80211_DEV(hw, &pdev->dev);

	bcma_set_drvdata(pdev, hw);

	memset(hw->priv, 0, sizeof(*wl));

	wl = brcms_attach(pdev);
	if (!wl) {
		pr_err("%s: brcms_attach failed!\n", __func__);
		return -ENODEV;
	}
	brcms_led_register(wl);

	return 0;
}
