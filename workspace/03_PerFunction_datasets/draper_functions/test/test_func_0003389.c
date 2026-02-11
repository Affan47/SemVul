wm8997_probe(struct platform_device *pdev)
{
	struct arizona *arizona = dev_get_drvdata(pdev->dev.parent);
	struct wm8997_priv *wm8997;
	int i;

	wm8997 = devm_kzalloc(&pdev->dev, sizeof(struct wm8997_priv),
			      GFP_KERNEL);
	if (wm8997 == NULL)
		return -ENOMEM;
	platform_set_drvdata(pdev, wm8997);

	wm8997->core.arizona = arizona;
	wm8997->core.num_inputs = 4;

	arizona_init_dvfs(&wm8997->core);

	for (i = 0; i < ARRAY_SIZE(wm8997->fll); i++)
		wm8997->fll[i].vco_mult = 1;

	arizona_init_fll(arizona, 1, ARIZONA_FLL1_CONTROL_1 - 1,
			 ARIZONA_IRQ_FLL1_LOCK, ARIZONA_IRQ_FLL1_CLOCK_OK,
			 &wm8997->fll[0]);
	arizona_init_fll(arizona, 2, ARIZONA_FLL2_CONTROL_1 - 1,
			 ARIZONA_IRQ_FLL2_LOCK, ARIZONA_IRQ_FLL2_CLOCK_OK,
			 &wm8997->fll[1]);


	regmap_update_bits(arizona->regmap, ARIZONA_SAMPLE_RATE_2,
			   ARIZONA_SAMPLE_RATE_2_MASK, 0x11);
	regmap_update_bits(arizona->regmap, ARIZONA_SAMPLE_RATE_3,
			   ARIZONA_SAMPLE_RATE_3_MASK, 0x12);

	for (i = 0; i < ARRAY_SIZE(wm8997_dai); i++)
		arizona_init_dai(&wm8997->core, i);


	for (i = 0; i < ARRAY_SIZE(wm8997_digital_vu); i++)
		regmap_update_bits(arizona->regmap, wm8997_digital_vu[i],
				   WM8997_DIG_VU, WM8997_DIG_VU);

	pm_runtime_enable(&pdev->dev);
	pm_runtime_idle(&pdev->dev);

	return snd_soc_register_codec(&pdev->dev, &soc_codec_dev_wm8997,
				      wm8997_dai, ARRAY_SIZE(wm8997_dai));
}
