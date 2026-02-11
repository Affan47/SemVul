rt286_index_sync(struct snd_soc_codec *codec)
{
	struct rt286_priv *rt286 = snd_soc_codec_get_drvdata(codec);
	int i;

	for (i = 0; i < INDEX_CACHE_SIZE; i++) {
		snd_soc_write(codec, rt286->index_cache[i].reg,
				  rt286->index_cache[i].def);
	}
}
