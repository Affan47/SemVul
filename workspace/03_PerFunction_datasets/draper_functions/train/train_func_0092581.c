sigget(sprite_t *s, int signal, void *data)
{
	mech_sprite_t *ms = (mech_sprite_t *)s;
	int xmax, ymax;
	switch(signal) {
	case SIGNAL_DAMAGE:
		sound_effect(&sound_bird, s->x, s->y);
		ms->damage += *(int *)data;
		if (ms->damage > 3) {


			init_position(s);
			ms->damage = 0;


			if (follow) {
				follow->state = 0;
				sprite_release(&follow);
			}
		}
		break;
	default:
		break;
	}
}
