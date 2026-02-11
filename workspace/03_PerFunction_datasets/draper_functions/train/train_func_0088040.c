stack_eq(const void *a, const void *b)
{
	const struct stackatom *sa = a, *sb = b;

	return sa->len == sb->len &&
		0 == memcmp(sa->stack, sb->stack, sa->len * sizeof sa->stack[0]);
}
