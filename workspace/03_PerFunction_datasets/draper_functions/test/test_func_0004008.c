fill_array(const void *key, void *value, void *user)
{
	struct filler *filler = user;
	struct leak *l;
	struct leak_record *lr = value;

	g_assert(filler->idx < filler->count);

	l = &filler->leaks[filler->idx++];
	switch (filler->kt) {
	case LEAK_KEY_PLACE:
		l->u.place = key;
		break;
	case LEAK_KEY_STACK:
		l->u.sa = key;
		break;
	}
	l->lr = lr;
}
