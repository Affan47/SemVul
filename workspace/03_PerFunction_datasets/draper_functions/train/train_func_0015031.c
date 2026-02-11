soc_cleanup_card_resources(struct snd_soc_card *card)
{
	int i;


	for (i = 0; i < card->num_rtd; i++) {
		struct snd_soc_pcm_runtime *rtd = &card->rtd[i];
		flush_delayed_work(&rtd->delayed_work);
	}


	for (i = 0; i < card->num_aux_devs; i++)
		soc_remove_aux_dev(card, i);


	snd_card_free(card->snd_card);


	soc_remove_dai_links(card);

	soc_cleanup_card_debugfs(card);


	if (card->remove)
		card->remove(card);

	snd_soc_dapm_free(&card->dapm);

	return 0;
}
