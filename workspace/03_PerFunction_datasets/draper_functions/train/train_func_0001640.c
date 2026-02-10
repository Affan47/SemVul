dac33_soc_probe(struct snd_soc_codec *codec)
{
	struct tlv320dac33_priv *dac33 = snd_soc_codec_get_drvdata(codec);
	int ret = 0;

	codec->control_data = dac33->control_data;
	codec->hw_write = (hw_write_t) i2c_master_send;
	dac33->codec = codec;


	ret = dac33_hard_power(codec, 1);
	if (ret != 0) {
		dev_err(codec->dev, "Failed to power up codec: %d\n", ret);
		goto err_power;
	}
	ret = dac33_read_id(codec);
	dac33_hard_power(codec, 0);

	if (ret < 0) {
		dev_err(codec->dev, "Failed to read chip ID: %d\n", ret);
		ret = -ENODEV;
		goto err_power;
	}


	if (dac33->irq >= 0) {
		ret = request_irq(dac33->irq, dac33_interrupt_handler,
				  IRQF_TRIGGER_RISING,
				  codec->component.name, codec);
		if (ret < 0) {
			dev_err(codec->dev, "Could not request IRQ%d (%d)\n",
						dac33->irq, ret);
			dac33->irq = -1;
		}
		if (dac33->irq != -1) {

			dac33->dac33_wq =
				create_singlethread_workqueue("tlv320dac33");
			if (dac33->dac33_wq == NULL) {
				free_irq(dac33->irq, codec);
				return -ENOMEM;
			}

			INIT_WORK(&dac33->work, dac33_work);
		}
	}


	if (dac33->irq >= 0)
		snd_soc_add_codec_controls(codec, dac33_mode_snd_controls,
				     ARRAY_SIZE(dac33_mode_snd_controls));

err_power:
	return ret;
}
