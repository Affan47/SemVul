davail_compare(const void *a, const void *b)
{
	struct search_idle_host_state *const *aa = a;
	struct search_idle_host_state *const *bb = b;
	const struct search_idle_host_state *p = *aa;
	const struct search_idle_host_state *q = *bb;
	const float df1 = p->diskavail;
	const float df2 = q->diskavail;

	if (df1 > df2)
		return (-1);
	else if (df1 < df2)
		return (1);
	else
		return (0);
}
