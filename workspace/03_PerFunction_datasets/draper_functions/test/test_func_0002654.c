amdtp_am824_set_pcm_position(struct amdtp_stream *s, unsigned int index,
				 unsigned int position)
{
	struct amdtp_am824 *p = s->protocol;

	if (index < p->pcm_channels)
		p->pcm_positions[index] = position;
}
