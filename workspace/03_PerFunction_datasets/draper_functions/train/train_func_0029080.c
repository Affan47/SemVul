asoc_simple_card_unref(struct snd_soc_card *card)
{
	struct snd_soc_dai_link *dai_link;
	int num_links;

	for (num_links = 0, dai_link = card->dai_link;
	     num_links < card->num_links;
	     num_links++, dai_link++) {
		of_node_put(dai_link->cpu_of_node);
		of_node_put(dai_link->codec_of_node);
	}
	return 0;
}
