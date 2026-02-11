get_selem_ctl(selem_none_t *s, int dir)
{
	selem_ctl_t *c;
	if (dir == SM_PLAY)
		c = &s->ctls[CTL_PLAYBACK_VOLUME];
	else if (dir == SM_CAPT)
		c = &s->ctls[CTL_CAPTURE_VOLUME];
	else
		return NULL;
	if (! c->elem) {
		c = &s->ctls[CTL_GLOBAL_VOLUME];
		if (! c->elem)
			return NULL;
	}
	if (c->type != SND_CTL_ELEM_TYPE_INTEGER)
		return NULL;
	return c;
}
