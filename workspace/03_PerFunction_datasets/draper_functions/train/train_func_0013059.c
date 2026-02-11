skl_pcm_prepare(struct snd_pcm_substream *substream,
		struct snd_soc_dai *dai)
{
	struct hdac_ext_stream *stream = get_hdac_ext_stream(substream);
	unsigned int format_val;
	int err;

	dev_dbg(dai->dev, "%s: %s\n", __func__, dai->name);
	if (hdac_stream(stream)->prepared) {
		dev_dbg(dai->dev, "already stream is prepared - returning\n");
		return 0;
	}

	format_val = skl_get_format(substream, dai);
	dev_dbg(dai->dev, "stream_tag=%d formatvalue=%d\n",
				hdac_stream(stream)->stream_tag, format_val);
	snd_hdac_stream_reset(hdac_stream(stream));

	err = snd_hdac_stream_set_params(hdac_stream(stream), format_val);
	if (err < 0)
		return err;

	err = snd_hdac_stream_setup(hdac_stream(stream));
	if (err < 0)
		return err;

	hdac_stream(stream)->prepared = 1;

	return err;
}
