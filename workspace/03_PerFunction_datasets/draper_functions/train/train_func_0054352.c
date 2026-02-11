data_append_markers(struct data d, struct marker *m)
{
	struct marker **mp = &d.markers;


	while (*mp)
		mp = &((*mp)->next);
	*mp = m;
	return d;
}
