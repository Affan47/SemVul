skl_pcm_hw_free(struct snd_pcm_substream *substream,
		struct snd_soc_dai *dai)
{
	struct hdac_ext_bus *ebus = dev_get_drvdata(dai->dev);
	struct hdac_ext_stream *stream = get_hdac_ext_stream(substream);

	dev_dbg(dai->dev, "%s: %s\n", __func__, dai->name);

	snd_hdac_stream_cleanup(hdac_stream(stream));
	hdac_stream(stream)->prepared = 0;

	return skl_substream_free_pages(ebus_to_hbus(ebus), substream);
}
