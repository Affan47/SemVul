wm8962_remove(struct snd_soc_codec *codec)
{
	struct wm8962_priv *wm8962 = snd_soc_codec_get_drvdata(codec);
	int i;

	cancel_delayed_work_sync(&wm8962->mic_work);

	wm8962_free_gpio(codec);
	wm8962_free_beep(codec);
	for (i = 0; i < ARRAY_SIZE(wm8962->supplies); i++)
		regulator_unregister_notifier(wm8962->supplies[i].consumer,
					      &wm8962->disable_nb[i]);

	return 0;
}
