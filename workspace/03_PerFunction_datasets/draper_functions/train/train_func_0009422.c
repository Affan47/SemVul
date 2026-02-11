soc_probe_component(struct snd_soc_card *card,
	struct snd_soc_component *component)
{
	struct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	struct snd_soc_dai *dai;
	int ret;

	if (!strcmp(component->name, "snd-soc-dummy"))
		return 0;

	if (component->card) {
		if (component->card != card) {
			dev_err(component->dev,
				"Trying to bind component to card \"%s\" but is already bound to card \"%s\"\n",
				card->name, component->card->name);
			return -ENODEV;
		}
		return 0;
	}

	if (!try_module_get(component->dev->driver->owner))
		return -ENODEV;

	component->card = card;
	dapm->card = card;
	soc_set_name_prefix(card, component);

	soc_init_component_debugfs(component);

	if (component->dapm_widgets) {
		ret = snd_soc_dapm_new_controls(dapm, component->dapm_widgets,
			component->num_dapm_widgets);

		if (ret != 0) {
			dev_err(component->dev,
				"Failed to create new controls %d\n", ret);
			goto err_probe;
		}
	}

	list_for_each_entry(dai, &component->dai_list, list) {
		ret = snd_soc_dapm_new_dai_widgets(dapm, dai);
		if (ret != 0) {
			dev_err(component->dev,
				"Failed to create DAI widgets %d\n", ret);
			goto err_probe;
		}
	}

	if (component->probe) {
		ret = component->probe(component);
		if (ret < 0) {
			dev_err(component->dev,
				"ASoC: failed to probe component %d\n", ret);
			goto err_probe;
		}

		WARN(dapm->idle_bias_off &&
			dapm->bias_level != SND_SOC_BIAS_OFF,
			"codec %s can not start from non-off bias with idle_bias_off==1\n",
			component->name);
	}

	if (component->controls)
		snd_soc_add_component_controls(component, component->controls,
				     component->num_controls);
	if (component->dapm_routes)
		snd_soc_dapm_add_routes(dapm, component->dapm_routes,
					component->num_dapm_routes);

	list_add(&dapm->list, &card->dapm_list);


	if (component->codec)
		list_add(&component->codec->card_list, &card->codec_dev_list);

	return 0;

err_probe:
	soc_cleanup_component_debugfs(component);
	component->card = NULL;
	module_put(component->dev->driver->owner);

	return ret;
}
