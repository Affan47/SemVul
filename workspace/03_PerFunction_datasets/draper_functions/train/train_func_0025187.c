from_user(selem_none_t *s, int dir, selem_ctl_t *c, long value)
{
	int64_t n;
	if (s->str[dir].max == s->str[dir].min)
		return c->min;
	n = (int64_t) (value - s->str[dir].min) * (c->max - c->min);
	return c->min + (n + (s->str[dir].max - s->str[dir].min) / 2) / (s->str[dir].max - s->str[dir].min);
}
