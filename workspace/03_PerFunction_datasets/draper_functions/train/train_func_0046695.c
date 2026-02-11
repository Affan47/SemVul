snd_pcm_plugin_free(struct snd_pcm_plugin *plugin)
{
	if (! plugin)
		return 0;
	if (plugin->private_free)
		plugin->private_free(plugin);
	kfree(plugin->buf_channels);
	vfree(plugin->buf);
	kfree(plugin);
	return 0;
}
