s_get_sprite(s_container_t *c, unsigned bank, unsigned frame)
{
	s_bank_t *b = s_get_bank(c, bank);
	if(!b)
		return NULL;
	if(frame > b->max)
		return NULL;
	return b->sprites[frame];
}
