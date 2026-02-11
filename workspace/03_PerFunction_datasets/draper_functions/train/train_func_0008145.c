getItem(int64_t key)
{
	STmpinfo *s = getItemPos(key);
	if (s)
		s->last_updated = getTick();
	return s ? s->data : NULL;
}
