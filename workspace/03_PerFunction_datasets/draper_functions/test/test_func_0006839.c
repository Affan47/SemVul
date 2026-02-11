snd_ac97_page_restore(struct snd_ac97 *ac97, int page_save)
{
	if (page_save >= 0) {
		snd_ac97_update_bits(ac97, AC97_INT_PAGING, AC97_PAGE_MASK, page_save);
		mutex_unlock(&ac97->page_mutex);
	}
}
