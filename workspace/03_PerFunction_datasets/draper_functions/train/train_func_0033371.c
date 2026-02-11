dpcm_fe_dai_startup(struct snd_pcm_substream *fe_substream)
{
	struct snd_soc_pcm_runtime *fe = fe_substream->private_data;
	struct snd_pcm_runtime *runtime = fe_substream->runtime;
	int stream = fe_substream->stream, ret = 0;

	dpcm_set_fe_update_state(fe, stream, SND_SOC_DPCM_UPDATE_FE);

	ret = dpcm_be_dai_startup(fe, fe_substream->stream);
	if (ret < 0) {
		dev_err(fe->dev,"ASoC: failed to start some BEs %d\n", ret);
		goto be_err;
	}

	dev_dbg(fe->dev, "ASoC: open FE %s\n", fe->dai_link->name);


	ret = soc_pcm_open(fe_substream);
	if (ret < 0) {
		dev_err(fe->dev,"ASoC: failed to start FE %d\n", ret);
		goto unwind;
	}

	fe->dpcm[stream].state = SND_SOC_DPCM_STATE_OPEN;

	dpcm_set_fe_runtime(fe_substream);
	snd_pcm_limit_hw_rates(runtime);

	dpcm_set_fe_update_state(fe, stream, SND_SOC_DPCM_UPDATE_NO);
	return 0;

unwind:
	dpcm_be_dai_startup_unwind(fe, fe_substream->stream);
be_err:
	dpcm_set_fe_update_state(fe, stream, SND_SOC_DPCM_UPDATE_NO);
	return ret;
}
