leak_init(void)
{
	struct leak_set *ls;

	XPMALLOC0(ls);
	ls->magic = LEAK_SET_MAGIC;
	ls->places = htable_create_real(HASH_KEY_STRING, 0);
	ls->stacks = htable_create_any_real(stack_hash, NULL, stack_eq);

	return ls;
}
