scalar_create_str(eval_scalar *s, const eval_str *t)
{
	s->type = SCALAR_STR;
	s->scalar.str.value = ht_malloc(t->len ? t->len : 1);
	memcpy(s->scalar.str.value, t->value, t->len);
	s->scalar.str.len = t->len;
}
