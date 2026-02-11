snd_pcm_link_ptr(snd_pcm_t *pcm, snd_pcm_rbptr_t *pcm_rbptr,
			     snd_pcm_t *slave, snd_pcm_rbptr_t *slave_rbptr)
{
	snd_pcm_t **a;
	int idx;

	a = slave_rbptr->link_dst;
	for (idx = 0; idx < slave_rbptr->link_dst_count; idx++)
		if (a[idx] == NULL) {
			a[idx] = pcm;
			goto __found_free_place;
		}
	a = realloc(a, sizeof(snd_pcm_t *) * (slave_rbptr->link_dst_count + 1));
	if (a == NULL) {
		pcm_rbptr->ptr = NULL;
		pcm_rbptr->fd = -1;
		pcm_rbptr->offset = 0UL;
		return;
	}
	a[slave_rbptr->link_dst_count++] = pcm;
      __found_free_place:
	pcm_rbptr->master = slave_rbptr->master ? slave_rbptr->master : slave;
	pcm_rbptr->ptr = slave_rbptr->ptr;
	pcm_rbptr->fd = slave_rbptr->fd;
	pcm_rbptr->offset = slave_rbptr->offset;
	slave_rbptr->link_dst = a;
	if (pcm_rbptr->changed)
		pcm_rbptr->changed(pcm, slave);
}
