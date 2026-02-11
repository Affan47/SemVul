config_prune_white(struct str_buff *s)
{

	while(s->len && isspace(*(unsigned char *)(s->t + s->len - 1)))
		s->len--;

	*(s->t + s->len) = '\0';

	return s->len;
}
