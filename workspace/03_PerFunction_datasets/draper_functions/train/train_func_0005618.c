snd_pcm_ioplug_poll_revents(snd_pcm_t *pcm, struct pollfd *pfds, unsigned int nfds, unsigned short *revents)
{
	ioplug_priv_t *io = pcm->private_data;

	if (io->data->callback->poll_revents)
		return io->data->callback->poll_revents(io->data, pfds, nfds, revents);
	else
		*revents = pfds->revents;
	return 0;
}
