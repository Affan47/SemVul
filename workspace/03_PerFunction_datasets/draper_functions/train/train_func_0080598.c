snd_pcm_hooks_hw_free(snd_pcm_t *pcm)
{
	snd_pcm_hooks_t *h = pcm->private_data;
	struct list_head *pos, *next;
	int err = snd_pcm_generic_hw_free(pcm);
	if (err < 0)
		return err;
	list_for_each_safe(pos, next, &h->hooks[SND_PCM_HOOK_TYPE_HW_FREE]) {
		snd_pcm_hook_t *hook = list_entry(pos, snd_pcm_hook_t, list);
		err = hook->func(hook);
		if (err < 0)
			return err;
	}
	return 0;
}
