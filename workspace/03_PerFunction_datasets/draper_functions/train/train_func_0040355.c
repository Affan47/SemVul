mix_exit(sfx_pcm_mixer_t *self)
{
	ACQUIRE_LOCK();
	while (self->feeds_nr)
		_mix_unsubscribe(self, self->feeds[0].feed);

	if (P->outbuf)
		sci_free(P->outbuf);
	if (P->writebuf)
		sci_free(P->writebuf);

	if (P->compbuf_l)
		sci_free(P->compbuf_l);
	if (P->compbuf_l)
		sci_free(P->compbuf_r);

	sci_free(P);
	self->private_bits  = NULL;
	RELEASE_LOCK();

#ifdef DEBUG
	sciprintf("[soft-mixer] Uninitialising mixer\n");
#endif
}
