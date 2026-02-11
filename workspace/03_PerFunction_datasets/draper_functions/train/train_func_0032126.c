callframe_cmp(const void *p1, const void *p2)
{
	const struct callframe *f1 = p1, *f2 = p2;

	return CMP(f2->calls, f1->calls);
}
