elem_write_volume(selem_none_t *s, int dir, selem_ctl_type_t type)
{
	snd_ctl_elem_value_t *ctl;
	unsigned int idx;
	int err;
	selem_ctl_t *c = &s->ctls[type];
	snd_ctl_elem_value_alloca(&ctl);
	if ((err = snd_hctl_elem_read(c->elem, ctl)) < 0)
		return err;
	for (idx = 0; idx < c->values; idx++)
		snd_ctl_elem_value_set_integer(ctl, idx, from_user(s, dir, c, s->str[dir].vol[idx]));
	if ((err = snd_hctl_elem_write(c->elem, ctl)) < 0)
		return err;
	return 0;
}
