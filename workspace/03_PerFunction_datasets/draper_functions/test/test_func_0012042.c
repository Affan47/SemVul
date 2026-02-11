skl_tplg_fe_get_cpr_module(struct snd_soc_dai *dai, int stream)
{
	struct snd_soc_dapm_widget *w;
	struct snd_soc_dapm_path *p = NULL;

	if (stream == SNDRV_PCM_STREAM_PLAYBACK) {
		w = dai->playback_widget;
		snd_soc_dapm_widget_for_each_sink_path(w, p) {
			if (p->connect && p->sink->power &&
					is_skl_dsp_widget_type(p->sink))
				continue;

			if (p->sink->priv) {
				dev_dbg(dai->dev, "set params for %s\n",
						p->sink->name);
				return p->sink->priv;
			}
		}
	} else {
		w = dai->capture_widget;
		snd_soc_dapm_widget_for_each_source_path(w, p) {
			if (p->connect && p->source->power &&
					is_skl_dsp_widget_type(p->source))
				continue;

			if (p->source->priv) {
				dev_dbg(dai->dev, "set params for %s\n",
						p->source->name);
				return p->source->priv;
			}
		}
	}

	return NULL;
}
