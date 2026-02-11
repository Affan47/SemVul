output_cmp_by_loadavg(const void *a, const void *b)
{
	const struct output *o1, *o2;

	if (output_sort_reverse) {
		o1 = b;
		o2 = a;
	} else {
		o1 = a;
		o2 = b;
	}
	if (!LOADAVG_AVAIL(o1) && !LOADAVG_AVAIL(o2))
		return (0);
	else if (!LOADAVG_AVAIL(o2))
		return (-1);
	else if (!LOADAVG_AVAIL(o1))
		return (1);
	else if (o1->load.loadavg_1min < o2->load.loadavg_1min)
		return (-1);
	else if (o1->load.loadavg_1min > o2->load.loadavg_1min)
		return (1);
	else
		return (0);
}
