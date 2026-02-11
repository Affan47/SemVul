selem_free(snd_mixer_elem_t *elem)
{
	struct selem_base *simple = snd_mixer_elem_get_private(elem);
	struct helem_base *hsimple;
	struct list_head *pos, *npos;

	if (simple->selem.id)
		snd_mixer_selem_id_free(simple->selem.id);
	list_for_each_safe(pos, npos, &simple->helems) {
		hsimple = list_entry(pos, struct helem_base, list);
		free(hsimple);
	}
	free(simple);
}
